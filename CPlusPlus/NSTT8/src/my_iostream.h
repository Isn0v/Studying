#pragma once
#include <stddef.h>
#include <string>
#include <string.h>
#include <ios>
#include <limits>

class IO
{
protected:
    char *buffer;
    size_t buffer_size_;
    size_t buffer_capacity_;

    void set_eof(bool eof);
    bool is_open_;
    bool eof_;

    void set_eof(bool eof);
    void resize_buffer();

public:
    IO(size_t buffer_capacity = 1024);
    
    virtual ~IO();
    virtual void close() = 0;

    bool is_open() const;
    bool get_eof() const;
};

class Reader : public IO
{
public:
    Reader(size_t buffer_capacity = 1024);

    void read(int value);
    void read(long value);
    void read(long long value);
    void read(float value);
    void read(double value);
    void read(char value);
    void read(bool value);
    void read(const std::string &value);

    void close() override;

    ~Reader();
};

class Writer : public IO{
protected:
    size_t caret_pos = 0;

public:
    Writer(size_t buffer_capacity, const char *buffer_);

    const std::string& get_buffer() const;

    int write_int();
    long write_long();
    long long write_long_long();
    float write_float();
    double write_double();
    char write_char();
    bool write_bool();

    const std::string& write_string(size_t size);

    void close() override;


    ~Writer();
};
