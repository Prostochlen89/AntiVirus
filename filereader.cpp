// ����� ��� �������� �����
bool CAVBFileReader::open(PCSTR FileName) {
    if (FileName == NULL) return false;

    // ������� ������� ����
    hFile.open(FileName, ios::in | ios::out | ios::binary);
    if (!hFile.is_open()) return false;

    // ������ ��������� �����
    CHAR Sign[3];
    hFile.read((PSTR)Sign, 3);
    if (memcmp(Sign, "AVB", 3)) {
        // ���� ��������� �� ���������, ������� ��� �������
        hFile.close(); // �������� ����� ��� ����������� ��������������
        return false;
    }

    // ������ ����� �������
    hFile.read((PSTR)&this->RecordCount, sizeof(DWORD));

    return true;
}

// ����� ��� ������ ��������� ������ �� �����
bool CAVBFileReader::readNextRecord(PSAVRecord Record) {
    if (Record == NULL ||!hFile.is_open()) return false;

    // ������ ���������� � ��������� ������
    hFile.read((PSTR)&Record->Signature.Offset, sizeof(DWORD)); // �������� ���������
    hFile.read((PSTR)&Record->Signature.Length, sizeof(DWORD)); // ������ ���������
    hFile.read((PSTR)&Record->Signature.Hash, 4 * sizeof(DWORD)); // ����������� �����

    // ������ ����� �����
    hFile.read((PSTR)&Record->NameLen, sizeof(BYTE)); // ������ �����

    // ��������� ������ ��� ��� � ������ ������ �����
    Record->allocName(Record->NameLen);
    hFile.read((PSTR)Record->Name, Record->NameLen); // ���

    return true;
}
