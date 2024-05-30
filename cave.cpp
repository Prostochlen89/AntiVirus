CAVBFile::CAVBFile() {
    this->RecordCount = 0;
}

//! Закрытие файла
void CAVBFile::close() {
    if (hFile.is_open()) {
        hFile.close();
    }
}

//! Проверка состояния файла
bool CAVBFile::is_open() {
    return hFile.is_open();
}

//! Получение числа записей
DWORD CAVBFile::getRecordCount() {
    return this->RecordCount;
}
