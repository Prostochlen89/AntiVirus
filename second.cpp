#ifndef _AVBFILE_H__INCLUDED_
#define _AVBFILE_H__INCLUDED_

#include
#include
#include "avrecord.h"

using namespace std;

/* Формат файла антивирусной базы

[AVB] // - Сигнатура
[RecordCount * 4 ] // - Число записей
[Records... ]

Record:
[Offset * 4 ] // - Смещение
[Lenght * 4 ] // - Размер
[Hash * 16 ] // - Контрольная сумма
[NameLen * 1 ] // - Размер имени
[Name... ] // - Имя зловреда

*/

//! Класс Файла антивирусной базы
typedef class CAVBFile {
protected:
    fstream hFile; // - Объект потока файла
    DWORD RecordCount; // - Число записей

public:
    CAVBFile();

    //! Закрытие файла
    virtual void close();

    //! Проверка состояния файла
    virtual bool is_open();

    //! Получение числа записей
    virtual DWORD getRecordCount();
} * PCAVBFile;

//! Класс для записи файла
typedef class CAVBFileWriter : public CAVBFile {
public:
    CAVBFileWriter() : CAVBFile() {}

    //! Открытие файла
    bool open(PCSTR FileName);

    //! Добавление записи в файл
    bool addRecord(PSAVRecord Record);
} * PCAVBFileWriter;

//! Класс для чтения файла
typedef class CAVBFileReader : public CAVBFile {
public:
    CAVBFileReader() : CAVBFile() {}

    //! Открытие файла
    bool open(PCSTR FileName);

    //! Чтение записи
    bool readNextRecord(PSAVRecord Record);
} * PCAVBFileReader;

#endif
