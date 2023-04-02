#include <iostream>
#include <cstdlib>

typedef int vector_value_t;

class Vector{
private:
    std::size_t capacity;
    std::size_t size;
    vector_value_t* array;

    static std::size_t get_capacity(std::size_t value){
        std::size_t capacity = 1;
        while (capacity <= value){
            capacity *= 2;
        }
        return capacity;
    }

    void resize_array(bool upgrade = true){
        if (upgrade){
            this->capacity *= 2;
        } else {
            this->capacity /= 2;
        }

        this->array = (vector_value_t*) realloc(this->array, sizeof(vector_value_t)*this->capacity);
    }

public:
    explicit Vector(std::size_t size = 0){
        this->capacity = get_capacity(size);
        this->size = size;
        this->array = new vector_value_t(capacity);
    }

    void push_back(vector_value_t value){
        if (size == capacity){
            resize_array();
        }
        array[size] = value;
        size += 1;
    }

    vector_value_t get_value(std::size_t index){
        if (index >= size){
            throw std::string("Index out of range!");
        }
        return array[index];
    }

    vector_value_t pop_back(){
        if (size * 4 == capacity){
            resize_array(false);
        }
        vector_value_t value = get_value(size - 1);
        this->size -= 1;
        return value;
    }

    ~Vector(){
        delete array;
    }
};


int main() {
    Vector vec = Vector();
    for (std::size_t i = 0; i < 10; i++){
        vec.push_back(i);
        std::cout << vec.get_value(i) << " ";
    }
    std::cout << std::endl;
    vec.pop_back();
    vec.get_value(7);

}
