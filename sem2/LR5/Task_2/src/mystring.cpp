#include "../include/mystring.h"
#include <cstring>
#include <stdexcept>

String::String() : _capacity(15), _size(0), _data(new CharT[_capacity + 1]{}) {}

String::String(const String &str)
    : _capacity(str._capacity),
    _size(str._size),
    _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), str._data.get(), _size * sizeof(CharT));
}

String::String(String &&str) noexcept
    : _capacity(str._capacity), _size(str._size), _data(std::move(str._data))
{
    str._capacity = 15;
    str._size = 0;
    str._data = std::unique_ptr<CharT[]>(new CharT[16]{});
}

String::String(size_type size, CharT chr)
    : _capacity(size > 15 ? size : 15),
    _size(size),
    _data(new CharT[_capacity + 1]{})
{
    for (size_type i = 0; i < _size; i++)
    {
        _data[i] = chr;
    }
}

String::String(const CharT *cstr)
    : _capacity(strlen(cstr) > 15 ? strlen(cstr) : 15),
    _size(strlen(cstr)),
    _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), cstr, strlen(cstr) * sizeof(CharT));
}

String::String(const CharT *cstr, size_type count)
    : _capacity(count > 15 ? count : 15),
    _size(count),
    _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), cstr, count);
}

String::String(const String &other, size_type pos)
    : _capacity(other._size - pos > 15 ? other._size - pos : 15),
    _size(other._size - pos),
    _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), other._data.get() + pos, other._size - pos);
}

String::String(const String &other, size_type pos, size_type count)
    : _capacity(count > 15 ? count : 15),
    _size(count),
    _data(new CharT[_capacity + 1]{})
{
    memcpy(_data.get(), other._data.get() + pos, count);
}

String::~String()
{
    _capacity = 0;
    _size = 0;
    _data.reset();
}

String &String::assign(const String &str)
{
    *this = String(str);
    return *this;
}

String &String::assign(String &&str) noexcept
{
    *this = std::move(str);
    return *this;
}

String &String::assign(size_type size, CharT chr)
{
    *this = String(size, chr);
    return *this;
}

String &String::assign(const CharT *cstr)
{
    *this = String(cstr);
    return *this;
}

String &String::assign(const CharT *cstr, size_type count)
{
    *this = String(cstr, count);
    return *this;
}

String &String::assign(const String &str, size_type pos, size_type count)
{
    *this = count == npos ? String(str, pos) : String(str, pos, count);
    return *this;
}

String &String::append(size_type count, CharT chr)
{
    if (_size + count > _capacity)
    {
        reserve(_size + count);
    }
    for (size_type i = _size; i < _size + count; i++)
    {
        _data[i] = chr;
    }
    _size += count;
    _data[_size] = 0;
    return *this;
}

String &String::append(const CharT *cstr)
{
    return append(cstr, strlen(cstr));
}

String &String::append(const CharT *cstr, size_type count)
{
    if (_size + count > _capacity)
    {
        reserve(_size + count);
    }
    memcpy(_data.get() + _size, cstr, count);
    _size += count;
    _data[_size] = 0;
    return *this;
}

String &String::append(const String &str)
{
    return append(str, 0, str.size());
}

String &String::append(const String &str, size_type pos, size_type count)
{
    if (count == npos || pos + count > str._size)
    {
        count = str._size - pos;
    }
    if (_size + count > _capacity)
    {
        reserve(_size + count);
    }
    memcpy(_data.get() + _size, str._data.get() + pos, count);
    _size += count;
    _data[_size] = 0;
    return *this;
}

String &String::erase(size_type index, size_type count)
{
    if (index >= _size) return *this;
    if (count == npos || index + count > _size)
    {
        count = _size - index;
    }
    memmove(_data.get() + index, _data.get() + index + count,
            (_size - index - count) * sizeof(CharT));
    _size -= count;
    _data[_size] = 0;
    return *this;
}

String &String::insert(size_type index, size_type count, CharT chr)
{
    if (index > _size) index = _size;
    if (_size + count > _capacity)
    {
        reserve(_size + count);
    }
    memmove(_data.get() + index + count, _data.get() + index,
            (_size - index) * sizeof(CharT));
    for (size_type i = index; i < index + count; i++)
    {
        _data[i] = chr;
    }
    _size += count;
    _data[_size] = 0;
    return *this;
}

String &String::insert(size_type index, const CharT *cstr)
{
    return insert(index, cstr, strlen(cstr));
}

String &String::insert(size_type index, const CharT *cstr, size_type count)
{
    if (index > _size) index = _size;
    if (_size + count > _capacity)
    {
        reserve(_size + count);
    }
    memmove(_data.get() + index + count, _data.get() + index,
            (_size - index) * sizeof(CharT));
    memcpy(_data.get() + index, cstr, count);
    _size += count;
    _data[_size] = 0;
    return *this;
}

String &String::insert(size_type index, const String &str)
{
    return insert(index, str._data.get(), str._size);
}

String &String::insert(size_type index, const String &str, size_type s_index,
                       size_type count)
{
    if (count == npos || s_index + count > str._size)
    {
        count = str._size - s_index;
    }
    return insert(index, str._data.get() + s_index, count);
}

String &String::replace(size_type pos, size_type count, const String &str)
{
    erase(pos, count);
    insert(pos, str);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const String &str)
{
    size_type pos = first - cbegin();
    size_type len = last - first;
    erase(pos, len);
    insert(pos, str);
    return *this;
}

String &String::replace(size_type pos, size_type count, const String &str,
                        size_type pos2, size_type count2)
{
    erase(pos, count);
    insert(pos, str, pos2, count2);
    return *this;
}

String &String::replace(size_type pos, size_type count, const CharT *cstr,
                        size_type count2)
{
    erase(pos, count);
    insert(pos, cstr, count2);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const CharT *cstr, size_type count2)
{
    size_type pos = first - cbegin();
    size_type len = last - first;
    erase(pos, len);
    insert(pos, cstr, count2);
    return *this;
}

String &String::replace(size_type pos, size_type count, const CharT *cstr)
{
    erase(pos, count);
    insert(pos, cstr);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        const CharT *cstr)
{
    size_type pos = first - cbegin();
    size_type len = last - first;
    erase(pos, len);
    insert(pos, cstr);
    return *this;
}

String &String::replace(size_type pos, size_type count, size_type count2,
                        CharT chr)
{
    erase(pos, count);
    insert(pos, count2, chr);
    return *this;
}

String &String::replace(const_iterator first, const_iterator last,
                        size_type count2, CharT chr)
{
    size_type pos = first - cbegin();
    size_type len = last - first;
    erase(pos, len);
    insert(pos, count2, chr);
    return *this;
}

String String::substr(size_type pos, size_type count) const
{
    if (pos >= _size) return String();
    if (count == npos || pos + count > _size)
    {
        count = _size - pos;
    }
    return {*this, pos, count};
}

void String::clear()
{
    _size = 0;
    if (_data)
    {
        _data[0] = 0;
    }
}

void String::pop_back()
{
    if (_size > 0)
    {
        _size--;
        _data[_size] = 0;
    }
}

void String::push_back(CharT chr)
{
    if (_size + 1 > _capacity)
    {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size] = chr;
    _size++;
    _data[_size] = 0;
}

void String::reserve(size_type new_cap)
{
    if (new_cap > _capacity)
    {
        auto *new_data = new CharT[new_cap + 1]{};
        for (size_type i = 0; i < _size; i++)
        {
            new_data[i] = _data[i];
        }
        _data.reset(new_data);
        _capacity = new_cap;
        _data[_size] = 0;
    }
}

void String::resize(size_type size)
{
    resize(size, CharT());
}

void String::resize(size_type size, CharT chr)
{
    if (size > _capacity)
    {
        reserve(size);
    }
    if (size > _size)
    {
        for (size_type i = _size; i < size; i++)
        {
            _data[i] = chr;
        }
    }
    _size = size;
    _data[_size] = 0;
}

void String::swap(String &other) noexcept
{
    std::swap(_capacity, other._capacity);
    std::swap(_size, other._size);
    _data.swap(other._data);
}

void String::shrink_to_fit()
{
    if (_size < _capacity)
    {
        auto *new_data = new CharT[_size + 1]{};
        for (size_type i = 0; i < _size; i++)
        {
            new_data[i] = _data[i];
        }
        _data.reset(new_data);
        _capacity = _size;
        _data[_size] = 0;
    }
}

bool String::empty() const
{
    return _size == 0;
}

int String::compare(const String &str) const
{
    return compare(0, _size, str, 0, str._size);
}

int String::compare(size_type pos1, size_type count1, const String &str) const
{
    return compare(pos1, count1, str, 0, str._size);
}

int String::compare(size_type pos1, size_type count1, const String &str,
                    size_type pos2, size_type count2) const
{
    if (pos1 > _size) return -1;
    if (pos2 > str._size) return 1;

    if (count1 > _size - pos1) count1 = _size - pos1;
    if (count2 > str._size - pos2) count2 = str._size - pos2;

    size_type rlen = count1 < count2 ? count1 : count2;
    for (size_type i = 0; i < rlen; i++)
    {
        if (_data[pos1 + i] < str._data[pos2 + i])
        {
            return -1;
        }
        if (_data[pos1 + i] > str._data[pos2 + i])
        {
            return 1;
        }
    }
    if (count1 < count2) return -1;
    if (count1 > count2) return 1;
    return 0;
}

int String::compare(const CharT *cstr) const
{
    return compare(0, _size, cstr, strlen(cstr));
}

int String::compare(size_type pos1, size_type count1, const CharT *cstr) const
{
    return compare(pos1, count1, cstr, strlen(cstr));
}

int String::compare(size_type pos1, size_type count1, const CharT *cstr,
                    size_type count2) const
{
    if (pos1 > _size) return -1;
    if (count1 > _size - pos1) count1 = _size - pos1;

    size_type rlen = count1 < count2 ? count1 : count2;
    for (size_type i = 0; i < rlen; i++)
    {
        if (_data[pos1 + i] < cstr[i])
        {
            return -1;
        }
        if (_data[pos1 + i] > cstr[i])
        {
            return 1;
        }
    }
    if (count1 < count2) return -1;
    if (count1 > count2) return 1;
    return 0;
}

String::CharT &String::at(size_type pos)
{
    if (pos >= _size) throw std::out_of_range("String::at");
    return _data[pos];
}

String::CharT &String::back()
{
    return _data[_size - 1];
}

String::CharT &String::front()
{
    return _data[0];
}

String::CharT *String::data() noexcept
{
    return _data.get();
}

const String::CharT &String::at(size_type pos) const
{
    if (pos >= _size) throw std::out_of_range("String::at");
    return _data[pos];
}

const String::CharT &String::back() const
{
    return _data[_size - 1];
}

const String::CharT &String::front() const
{
    return _data[0];
}

const String::CharT *String::data() const
{
    return _data.get();
}

const String::CharT *String::c_str() const
{
    return _data.get();
}

String::size_type String::capacity() const
{
    return _capacity;
}

String::size_type String::size() const
{
    return _size;
}

String::size_type String::length() const
{
    return _size;
}

String::size_type String::max_size() const
{
    return npos / sizeof(CharT);
}

String::size_type String::copy(CharT *dest, size_type count,
                               size_type pos) const
{
    if (pos > _size) return 0;
    if (count > _size - pos) count = _size - pos;
    for (size_type i = 0; i < count; i++)
    {
        dest[i] = _data[pos + i];
    }
    return count;
}

String::size_type String::find(const String &str, size_type pos) const
{
    if (pos > _size) return npos;
    if (str.empty()) return pos;

    for (size_type i = pos; i <= _size - str._size; i++)
    {
        bool found = true;
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i + j] != str._data[j])
            {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return npos;
}

String::size_type String::find(const CharT *cstr, size_type pos,
                               size_type count) const
{
    if (pos > _size) return npos;
    if (count == 0) return pos;

    for (size_type i = pos; i <= _size - count; i++)
    {
        bool found = true;
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i + j] != cstr[j])
            {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return npos;
}

String::size_type String::find(const CharT *cstr, size_type pos) const
{
    return find(cstr, pos, strlen(cstr));
}

String::size_type String::find(CharT chr, size_type pos) const
{
    if (pos >= _size) return npos;
    for (size_type i = pos; i < _size; i++)
    {
        if (_data[i] == chr) return i;
    }
    return npos;
}

String::size_type String::rfind(const String &str, size_type pos) const
{
    if (str.empty()) return pos < _size ? pos : _size;
    if (str._size > _size) return npos;

    size_type start = pos < _size - str._size ? pos : _size - str._size;
    for (size_type i = start + 1; i > 0; i--)
    {
        bool found = true;
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i - 1 + j] != str._data[j])
            {
                found = false;
                break;
            }
        }
        if (found) return i - 1;
    }
    return npos;
}

String::size_type String::rfind(const CharT *cstr, size_type pos,
                                size_type count) const
{
    if (count == 0) return pos < _size ? pos : _size;
    if (count > _size) return npos;

    size_type start = pos < _size - count ? pos : _size - count;
    for (size_type i = start + 1; i > 0; i--)
    {
        bool found = true;
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i - 1 + j] != cstr[j])
            {
                found = false;
                break;
            }
        }
        if (found) return i - 1;
    }
    return npos;
}

String::size_type String::rfind(const CharT *cstr, size_type pos) const
{
    return rfind(cstr, pos, strlen(cstr));
}

String::size_type String::rfind(CharT chr, size_type pos) const
{
    if (_size == 0) return npos;
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        if (_data[i - 1] == chr) return i - 1;
    }
    return npos;
}

String::size_type String::find_first_of(const String &str, size_type pos) const
{
    for (size_type i = pos; i < _size; i++)
    {
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i] == str._data[j]) return i;
        }
    }
    return npos;
}

String::size_type String::find_first_of(const CharT *cstr, size_type pos,
                                        size_type count) const
{
    for (size_type i = pos; i < _size; i++)
    {
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i] == cstr[j]) return i;
        }
    }
    return npos;
}

String::size_type String::find_first_of(const CharT *cstr, size_type pos) const
{
    return find_first_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_first_of(CharT chr, size_type pos) const
{
    return find(chr, pos);
}

String::size_type String::find_first_not_of(const String &str, size_type pos) const
{
    for (size_type i = pos; i < _size; i++)
    {
        bool found = false;
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i] == str._data[j])
            {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }
    return npos;
}

String::size_type String::find_first_not_of(const CharT *cstr, size_type pos,
                                            size_type count) const
{
    for (size_type i = pos; i < _size; i++)
    {
        bool found = false;
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i] == cstr[j])
            {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }
    return npos;
}

String::size_type String::find_first_not_of(const CharT *cstr, size_type pos) const
{
    return find_first_not_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_first_not_of(CharT chr, size_type pos) const
{
    for (size_type i = pos; i < _size; i++)
    {
        if (_data[i] != chr) return i;
    }
    return npos;
}

String::size_type String::find_last_of(const String &str, size_type pos) const
{
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i - 1] == str._data[j]) return i - 1;
        }
    }
    return npos;
}

String::size_type String::find_last_of(const CharT *cstr, size_type pos,
                                       size_type count) const
{
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i - 1] == cstr[j]) return i - 1;
        }
    }
    return npos;
}

String::size_type String::find_last_of(const CharT *cstr, size_type pos) const
{
    return find_last_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_last_of(CharT chr, size_type pos) const
{
    return rfind(chr, pos);
}

String::size_type String::find_last_not_of(const String &str, size_type pos) const
{
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        bool found = false;
        for (size_type j = 0; j < str._size; j++)
        {
            if (_data[i - 1] == str._data[j])
            {
                found = true;
                break;
            }
        }
        if (!found) return i - 1;
    }
    return npos;
}

String::size_type String::find_last_not_of(const CharT *cstr, size_type pos,
                                           size_type count) const
{
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        bool found = false;
        for (size_type j = 0; j < count; j++)
        {
            if (_data[i - 1] == cstr[j])
            {
                found = true;
                break;
            }
        }
        if (!found) return i - 1;
    }
    return npos;
}

String::size_type String::find_last_not_of(const CharT *cstr, size_type pos) const
{
    return find_last_not_of(cstr, pos, strlen(cstr));
}

String::size_type String::find_last_not_of(CharT chr, size_type pos) const
{
    size_type start = pos < _size ? pos : _size - 1;
    for (size_type i = start + 1; i > 0; i--)
    {
        if (_data[i - 1] != chr) return i - 1;
    }
    return npos;
}

String::iterator String::erase(iterator position)
{
    size_type index = position - begin();
    erase(index, 1);
    return begin() + index;
}

String::iterator String::erase(iterator first, iterator last)
{
    size_type index = first - begin();
    size_type count = last - first;
    erase(index, count);
    return begin() + index;
}

String::iterator String::insert(const_iterator pos, CharT chr)
{
    return insert(pos, 1, chr);
}

String::iterator String::insert(const_iterator pos, size_type count, CharT chr)
{
    size_type index = pos - cbegin();
    insert(index, count, chr);
    return begin() + index;
}

String::iterator String::begin() { return {_data.get()}; }

String::iterator String::end() { return {_data.get() + _size}; }

String::const_iterator String::begin() const { return {_data.get()}; }

String::const_iterator String::cbegin() const noexcept { return {_data.get()}; }

String::const_iterator String::end() const { return {_data.get() + _size}; }

String::const_iterator String::cend() const noexcept
{
    return {_data.get() + _size};
}

String::reverse_iterator String::rbegin() { return {_data.get() + _size}; }

String::reverse_iterator String::rend() { return {_data.get()}; }

String::const_reverse_iterator String::rbegin() const { return crbegin(); }

String::const_reverse_iterator String::crbegin() const noexcept
{
    return {_data.get() + _size};
}

String::const_reverse_iterator String::crend() const noexcept
{
    return {_data.get()};
}

bool String::starts_with(const CharT *cstr) const
{
    size_type len = strlen(cstr);
    if (len > _size) return false;
    for (size_type i = 0; i < len; i++)
    {
        if (_data[i] != cstr[i]) return false;
    }
    return true;
}

bool String::ends_with(const CharT *cstr) const
{
    size_type len = strlen(cstr);
    if (len > _size) return false;
    for (size_type i = 0; i < len; i++)
    {
        if (_data[_size - len + i] != cstr[i]) return false;
    }
    return true;
}

bool String::contains(const CharT *cstr) const
{
    return find(cstr) != npos;
}

String &String::operator=(const String &string)
{
    if (this != &string)
    {
        clear();
        _size = string._size;
        if (_size > _capacity)
        {
            reserve(_size);
        }
        memcpy(_data.get(), string._data.get(), _size * sizeof(CharT));
        _data[_size] = 0;
    }
    return *this;
}

String &String::operator=(String &&string) noexcept
{
    if (this != &string)
    {
        _data = std::move(string._data);
        _capacity = string._capacity;
        _size = string._size;
        string._capacity = 15;
        string._size = 0;
        string._data = std::unique_ptr<CharT[]>(new CharT[16]{});
    }
    return *this;
}

String &String::operator=(const CharT *cstr)
{
    clear();
    _size = strlen(cstr);
    if (_size > _capacity)
    {
        reserve(_size);
    }
    memcpy(_data.get(), cstr, _size * sizeof(CharT));
    _data[_size] = 0;
    return *this;
}

String &String::operator=(CharT chr)
{
    clear();
    _size = 1;
    _data[0] = chr;
    _data[1] = 0;
    return *this;
}

String &String::operator+=(const String &str)
{
    append(str);
    return *this;
}

String &String::operator+=(CharT chr)
{
    push_back(chr);
    return *this;
}

String &String::operator+=(const CharT *cstr)
{
    append(cstr);
    return *this;
}

bool String::operator==(const String &str) const
{
    return compare(str) == 0;
}

bool String::operator==(const CharT *cstr) const
{
    return compare(cstr) == 0;
}

bool String::operator!=(const String &str) const
{
    return !(*this == str);
}

bool String::operator!=(const CharT *cstr) const
{
    return !(*this == cstr);
}

String::CharT &String::operator[](size_type pos)
{
    return _data[pos];
}

const String::CharT &String::operator[](size_type pos) const
{
    return _data[pos];
}

String operator+(const String &lhs, const String &rhs)
{
    String res = lhs;
    res.append(rhs);
    return res;
}

String operator+(const String &lhs, const String::CharT *rhs)
{
    String res = lhs;
    res.append(rhs);
    return res;
}

String operator+(const String &lhs, String::CharT rhs)
{
    String res = lhs;
    res.push_back(rhs);
    return res;
}

String operator+(const String::CharT *lhs, const String &rhs)
{
    String res = rhs;
    res.insert(0, lhs);
    return res;
}

String operator+(String::CharT lhs, const String &rhs)
{
    String res = rhs;
    res.insert(res.cbegin(), lhs);
    return res;
}

String operator+(String &&lhs, String &&rhs)
{
    lhs.append(std::move(rhs));
    return std::move(lhs);
}

String operator+(String &&lhs, const String &rhs)
{
    lhs.append(rhs);
    return std::move(lhs);
}

String operator+(String &&lhs, const String::CharT *rhs)
{
    lhs.append(rhs);
    return std::move(lhs);
}

String operator+(String &&lhs, String::CharT rhs)
{
    lhs.push_back(rhs);
    return std::move(lhs);
}

String operator+(const String &lhs, String &&rhs)
{
    rhs.insert(0, lhs);
    return std::move(rhs);
}

String operator+(const String::CharT *lhs, String &&rhs)
{
    rhs.insert(0, lhs);
    return std::move(rhs);
}

String operator+(String::CharT lhs, String &&rhs)
{
    rhs.insert(rhs.cbegin(), lhs);
    return std::move(rhs);
}

String operator""_s(const char *cstr, size_t len)
{
    return {cstr, len};
}

std::ostream &operator<<(std::ostream &ost, const String &str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        ost << str[i];
    }
    return ost;
}

std::istream &operator>>(std::istream &ist, String &str)
{
    str.clear();
    char ch;
    while (ist.get(ch) && ch != ' ' && ch != '\n' && ch != '\t')
    {
        str.push_back(ch);
    }
    return ist;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    const auto *c_src = static_cast<const unsigned char *>(src);
    for (size_t i = 0; i < count; i++)
    {
        c_dest[i] = c_src[i];
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    const auto *c_src = static_cast<const unsigned char *>(src);
    if (c_dest <= c_src || c_dest >= c_src + count)
    {
        for (size_t i = 0; i < count; i++)
        {
            c_dest[i] = c_src[i];
        }
    }
    else
    {
        for (size_t i = count; i > 0; i--)
        {
            c_dest[i - 1] = c_src[i - 1];
        }
    }
    return dest;
}

void *memset(void *dest, int chr, size_t count)
{
    auto *c_dest = static_cast<unsigned char *>(dest);
    auto value = static_cast<unsigned char>(chr);
    for (size_t i = 0; i < count; i++)
    {
        c_dest[i] = value;
    }
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *strncpy(char *dest, const char *src, size_t count)
{
    size_t i = 0;
    while (i < count && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < count)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *strcat(char *dest, const char *src)
{
    size_t dest_len = strlen(dest);
    size_t i = 0;
    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *strncat(char *dest, const char *src, size_t count)
{
    size_t dest_len = strlen(dest);
    size_t i = 0;
    while (i < count && src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *strtok(char *str, const char *delim)
{
    static char *buffer = nullptr;
    if (str != nullptr)
    {
        buffer = str;
    }
    if (buffer == nullptr || *buffer == '\0')
    {
        return nullptr;
    }

    buffer += strspn(buffer, delim);
    if (*buffer == '\0')
    {
        return nullptr;
    }

    char *token = buffer;
    buffer = strpbrk(buffer, delim);
    if (buffer != nullptr)
    {
        *buffer = '\0';
        buffer++;
    }
    return token;
}

const char *my_sys_errlist[SYS_ERRLIST_SIZE] = {
    [0] = "Operation succeeded",
    [EPERM] = "Operation not permitted",
    [ENOENT] = "No such file or directory",
    [ESRCH] = "No such process",
    [EINTR] = "Interrupted system call",
    [EIO] = "I/O error",
    [ENXIO] = "No such device or address",
    [E2BIG] = "Argument list too long",
    [ENOEXEC] = "Exec format error",
    [EBADF] = "Bad file number",
    [ECHILD] = "No child processes",
    [EAGAIN] = "Try again",
    [ENOMEM] = "Out of memory",
    [EACCES] = "Permission denied",
    [EFAULT] = "Bad address",
    [ENOTBLK] = "Block device required",
    [EBUSY] = "Device or resource busy",
    [EEXIST] = "File exists",
    [EXDEV] = "Cross-device link",
    [ENODEV] = "No such device",
    [ENOTDIR] = "Not a directory",
    [EISDIR] = "Is a directory",
    [EINVAL] = "Invalid argument",
    [ENFILE] = "File table overflow",
    [EMFILE] = "Too many open files",
    [ENOTTY] = "Not a typewriter",
    [ETXTBSY] = "Text file busy",
    [EFBIG] = "File too large",
    [ENOSPC] = "No space left on device",
    [ESPIPE] = "Illegal seek",
    [EROFS] = "Read-only file system",
    [EMLINK] = "Too many links",
    [EPIPE] = "Broken pipe",
    [EDOM] = "Math argument out of domain of func",
    [ERANGE] = "Math result not representable"
};

char *strerror(int errnum)
{
    auto *errmsg = new char[100]{};
    if (errnum >= 0 && errnum < SYS_ERRLIST_SIZE && my_sys_errlist[errnum] != nullptr)
    {
        strcpy(errmsg, my_sys_errlist[errnum]);
    }
    return errmsg;
}

int memcmp(const void *lhs, const void *rhs, size_t count)
{
    const auto *c_lhs = static_cast<const unsigned char *>(lhs);
    const auto *c_rhs = static_cast<const unsigned char *>(rhs);
    for (size_t i = 0; i < count; i++)
    {
        if (c_lhs[i] < c_rhs[i]) return -1;
        if (c_lhs[i] > c_rhs[i]) return 1;
    }
    return 0;
}

int strcmp(const char *lhs, const char *rhs)
{
    size_t i = 0;
    while (lhs[i] != '\0' && rhs[i] != '\0')
    {
        if (lhs[i] < rhs[i]) return -1;
        if (lhs[i] > rhs[i]) return 1;
        i++;
    }
    if (lhs[i] == '\0' && rhs[i] == '\0') return 0;
    if (lhs[i] == '\0') return -1;
    return 1;
}

int strncmp(const char *lhs, const char *rhs, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (lhs[i] == '\0' || rhs[i] == '\0')
        {
            if (lhs[i] == rhs[i]) return 0;
            if (lhs[i] == '\0') return -1;
            return 1;
        }
        if (lhs[i] < rhs[i]) return -1;
        if (lhs[i] > rhs[i]) return 1;
    }
    return 0;
}

int strcoll(const char *lhs, const char *rhs)
{
    return strcmp(lhs, rhs);
}

size_t strxfrm(char *dest, const char *src, size_t count)
{
    strncpy(dest, src, count);
    return strlen(src);
}

size_t strlen(const char *str)
{
    const char *end = str;
    while (*end != '\0')
    {
        end++;
    }
    return end - str;
}

size_t strspn(const char *dest, const char *src)
{
    char charset[256] = {0};
    for (size_t i = 0; src[i] != '\0'; i++)
    {
        charset[static_cast<unsigned char>(src[i])] = 1;
    }
    size_t count = 0;
    while (dest[count] != '\0' && charset[static_cast<unsigned char>(dest[count])])
    {
        count++;
    }
    return count;
}

size_t strcspn(const char *dest, const char *src)
{
    char charset[256] = {0};
    for (size_t i = 0; src[i] != '\0'; i++)
    {
        charset[static_cast<unsigned char>(src[i])] = 1;
    }
    size_t count = 0;
    while (dest[count] != '\0' && !charset[static_cast<unsigned char>(dest[count])])
    {
        count++;
    }
    return count;
}
