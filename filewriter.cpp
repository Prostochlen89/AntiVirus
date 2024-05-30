// ����� ��� �������� �����
bool CAVBFileWriter::open(PCSTR FileName) {
    if (FileName == NULL) return false;

    // �������� �����, ���� �� �� ����������
    if (!isFileExist(FileName)) {
        hFile.open(FileName, ios::out | ios::binary);
        if (!hFile.is_open()) return false;

        // ������ ��������� �����
        hFile.write("AVB", 3); // ��������� �����
        // ������ ���������� �������� �������� �������
        hFile.write((PCSTR)&this->RecordCount, sizeof(DWORD)); // ����� �������
    } else {
        // �������� ������������� ����� ��� ������ � ������
        hFile.open(FileName, ios::in | ios::out | ios::binary);
        if (!hFile.is_open()) return false;

        // �������� ��������� �����
        CHAR Sign[3];
        hFile.read((PSTR)Sign, 3);
        if (memcmp(Sign, "AVB", 3)) {
            // �������� �����, ���� ��������� �� ���������
            hFile.close(); // ��� ����� ����
            return false;
        }

        // ������ �������� �������� �������� �������
        hFile.read((PSTR)&this->RecordCount, sizeof(DWORD));
    }

    return true;
}

// ����� ��� ���������� ������ � ����
bool CAVBFileWriter::addRecord(PSAVRecord Record) {
    if (Record == NULL ||!hFile.is_open()) return false;

    // ����������� ��������� � ����� �����
    hFile.seekp(0, ios::end);

    // ������ ���������� � ����� ������
    hFile.write((PSTR)&Record->Signature.Offset, sizeof(DWORD)); // �������� ���������
    hFile.write((PSTR)&Record->Signature.Length, sizeof(DWORD)); // ������ ���������
    hFile.write((PSTR)&Record->Signature.Hash, 4 * sizeof(DWORD)); // ����������� �����
    hFile.write((PSTR)&Record->NameLen, sizeof(BYTE)); // ������ �����
    hFile.write((PSTR)Record->Name, Record->NameLen); // ���

    // ����������� ��������� � �����, ��� �������� ������� �������
    hFile.seekp(3, ios::beg);
    // ���������� �������� �������
    this->RecordCount++;
    hFile.write((PSTR)&this->RecordCount, sizeof(DWORD));

    return true;
}
