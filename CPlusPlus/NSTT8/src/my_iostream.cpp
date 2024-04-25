#include "my_iostream.h"

bool IO::is_open() const
{
    return is_open_;
}

void IO::set_eof(bool eof)
{
    eof_ = eof;
}

void IO::resize_buffer()
{
    char *new_buffer = new char[buffer_capacity_ *= 2];
    memcpy(new_buffer, buffer, buffer_size_);
    delete[] buffer;
    buffer = new_buffer;
}

IO::IO(size_t buffer_capacity = 1024) : buffer_capacity_(buffer_capacity),
                                        buffer_size_(0),
                                        buffer(new char[buffer_capacity_]),
                                        eof_(false),
                                        is_open_(true)
{
}

IO::~IO()
{
    delete[] buffer;
}

bool IO::get_eof() const
{
    return eof_;
}

void Reader::read(long value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[21];
    int size = snprintf(buffer, sizeof(buffer), "%ld", value);
    this->read(std::string(buffer, size));
}

Reader::Reader(size_t buffer_capacity = 1024) : IO(buffer_capacity)
{
}

void Reader::read(int value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[11];
    int size = snprintf(buffer, sizeof(buffer), "%d", value);
    this->read(std::string(buffer, size));
}

void Reader::read(long long value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[21];
    int size = snprintf(buffer, sizeof(buffer), "%lld", value);
    this->read(std::string(buffer, size));
}

void Reader::read(float value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[24];
    int size = snprintf(buffer, sizeof(buffer), "%.7g", value);
    this->read(std::string(buffer, size));
}

void Reader::read(double value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[40];
    int size = snprintf(buffer, sizeof(buffer), "%.17g", value);
    this->read(std::string(buffer, size));
}

void Reader::read(char value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    char buffer[2];
    buffer[0] = value;
    buffer[1] = '\0';
    this->read(std::string(buffer));
}

void Reader::read(bool value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    this->read(value ? "true" : "false");
}

void Reader::read(const std::string &value)
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Reader is not open");
    }
    if (value.size() + 2 > buffer_capacity_)
    {
        resize_buffer();
    }
    memcpy(buffer + buffer_size_, value.c_str(), value.size());
    buffer_size_ += value.size();
    buffer[buffer_size_] = '\0';
}

void Reader::close()
{
    is_open_ = false;
    set_eof(true);
    buffer_size_ = 0;
}

Reader::~Reader()
{
    delete[] buffer;
}

Writer::Writer(size_t buffer_capacity, const char *buffer_) : IO(buffer_capacity)
{
    if (buffer != nullptr)
    {
        memcpy(buffer, buffer_, buffer_size_);
        delete[] buffer_;
    }
}

size_t find_delimiter(const char *buffer, size_t buffer_size, char delimiter)
{
    for (size_t i = 0; i < buffer_size; ++i)
    {
        if (buffer[i] == delimiter)
        {
            return i;
        }
    }
    return buffer_size;
}

const std::string &Writer::get_buffer() const
{
    return std::string(buffer, buffer_size_);
}

int Writer::write_int()
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Writer is not open");
    }
    if (eof_)
    {
        throw std::ios_base::failure("Nothing to write");
    }
    long long value = write_long_long();
    if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
    {
        
    }
    return static_cast<int>(value);
}

long Writer::write_long()
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Writer is not open");
    }
    if (eof_)
    {
        throw std::ios_base::failure("Nothing to write");
    }
    if (caret_pos + 21 > buffer_size_)
    {
        set_eof(true);
        char tmp[buffer_size_ - caret_pos + 1];
        memcpy(tmp, buffer + caret_pos, buffer_size_ - caret_pos);
        tmp[buffer_size_ - caret_pos] = '\0';
    }
    else
    {
        char tmp[21];
        memcpy(tmp, buffer + caret_pos, 20);
        tmp[20] = '\0';
        caret_pos += 21;
        return std::stoll(tmp);
    }
}

long long Writer::write_long_long()
{
    if (!is_open_)
    {
        throw std::ios_base::failure("Writer is not open");
    }
    if (eof_)
    {
        throw std::ios_base::failure("Nothing to write");
    }
    if (caret_pos + 20 > buffer_size_)
    {
        size_t delimiter_pos = find_delimiter(buffer + caret_pos, buffer_size_ - caret_pos, ' ');
        if (delimiter_pos == buffer_size_ - caret_pos)
        {
            delimiter_pos = find_delimiter(buffer + caret_pos, buffer_size_ - caret_pos, '\n');
            if (delimiter_pos == buffer_size_ - caret_pos)
            {
                set_eof(true);
                char tmp[buffer_size_ - caret_pos + 1];
                memcpy(tmp, buffer + caret_pos, buffer_size_ - caret_pos);
                tmp[buffer_size_ - caret_pos] = '\0';
                return std::stoll(tmp);
            }
            else
            {
                char tmp[delimiter_pos - caret_pos + 1];
                memcpy(tmp, buffer + caret_pos, delimiter_pos - caret_pos);
                tmp[delimiter_pos - caret_pos] = '\0';
                caret_pos = delimiter_pos + 1;
                return std::stoll(tmp);
            }
        }
        else
        {
            char tmp[delimiter_pos - caret_pos + 1];
            memcpy(tmp, buffer + caret_pos, delimiter_pos - caret_pos);
            tmp[delimiter_pos - caret_pos] = '\0';
            caret_pos = delimiter_pos + 1;
            return std::stoll(tmp);
        }
    }
    else
    {
        char tmp[20];
        memcpy(tmp, buffer + caret_pos, 10);
        tmp[19] = '\0';
        caret_pos += 20;
        return std::stoll(tmp);
    }
}
