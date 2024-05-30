// Метод для открытия файла
bool CAVBFileReader::open(PCSTR FileName) {
    if (FileName == NULL) return false;

    // Попытка открыть файл
    hFile.open(FileName, ios::in | ios::out | ios::binary);
    if (!hFile.is_open()) return false;

    // Чтение сигнатуры файла
    CHAR Sign[3];
    hFile.read((PSTR)Sign, 3);
    if (memcmp(Sign, "AVB", 3)) {
        // Если сигнатура не совпадает, считаем это ошибкой
        hFile.close(); // Закрытие файла при обнаружении несоответствия
        return false;
    }

    // Чтение числа записей
    hFile.read((PSTR)&this->RecordCount, sizeof(DWORD));

    return true;
}

// Метод для чтения следующей записи из файла
bool CAVBFileReader::readNextRecord(PSAVRecord Record) {
    if (Record == NULL ||!hFile.is_open()) return false;

    // Чтение информации о сигнатуре записи
    hFile.read((PSTR)&Record->Signature.Offset, sizeof(DWORD)); // Смещение сигнатуры
    hFile.read((PSTR)&Record->Signature.Length, sizeof(DWORD)); // Размер сигнатуры
    hFile.read((PSTR)&Record->Signature.Hash, 4 * sizeof(DWORD)); // Контрольная сумма

    // Чтение длины имени
    hFile.read((PSTR)&Record->NameLen, sizeof(BYTE)); // Размер имени

    // Выделение памяти под имя и чтение самого имени
    Record->allocName(Record->NameLen);
    hFile.read((PSTR)Record->Name, Record->NameLen); // Имя

    return true;
}
