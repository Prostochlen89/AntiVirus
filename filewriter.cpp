// Метод для открытия файла
bool CAVBFileWriter::open(PCSTR FileName) {
    if (FileName == NULL) return false;

    // Создание файла, если он не существует
    if (!isFileExist(FileName)) {
        hFile.open(FileName, ios::out | ios::binary);
        if (!hFile.is_open()) return false;

        // Запись сигнатуры файла
        hFile.write("AVB", 3); // Сигнатура файла
        // Запись начального значения счетчика записей
        hFile.write((PCSTR)&this->RecordCount, sizeof(DWORD)); // Число записей
    } else {
        // Открытие существующего файла для чтения и записи
        hFile.open(FileName, ios::in | ios::out | ios::binary);
        if (!hFile.is_open()) return false;

        // Проверка сигнатуры файла
        CHAR Sign[3];
        hFile.read((PSTR)Sign, 3);
        if (memcmp(Sign, "AVB", 3)) {
            // Закрытие файла, если сигнатура не совпадает
            hFile.close(); // Это чужой файл
            return false;
        }

        // Чтение текущего значения счетчика записей
        hFile.read((PSTR)&this->RecordCount, sizeof(DWORD));
    }

    return true;
}

// Метод для добавления записи в файл
bool CAVBFileWriter::addRecord(PSAVRecord Record) {
    if (Record == NULL ||!hFile.is_open()) return false;

    // Перемещение указателя в конец файла
    hFile.seekp(0, ios::end);

    // Запись информации о новой записи
    hFile.write((PSTR)&Record->Signature.Offset, sizeof(DWORD)); // Смещение сигнатуры
    hFile.write((PSTR)&Record->Signature.Length, sizeof(DWORD)); // Размер сигнатуры
    hFile.write((PSTR)&Record->Signature.Hash, 4 * sizeof(DWORD)); // Контрольная сумма
    hFile.write((PSTR)&Record->NameLen, sizeof(BYTE)); // Размер имени
    hFile.write((PSTR)Record->Name, Record->NameLen); // Имя

    // Перемещение указателя к месту, где хранится счетчик записей
    hFile.seekp(3, ios::beg);
    // Увеличение счетчика записей
    this->RecordCount++;
    hFile.write((PSTR)&this->RecordCount, sizeof(DWORD));

    return true;
}
