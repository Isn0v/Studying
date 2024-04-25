template <typename T>
class ScopedPointerDeep {
public:
    explicit ScopedPointerDeep(T* ptr = nullptr) : m_ptr(ptr) {}
    
    ~ScopedPointerDeep() {
        delete m_ptr;
    }
    
    ScopedPointerDeep(const ScopedPointerDeep& other) : m_ptr(new T(*other.m_ptr)) {}
    
    ScopedPointerDeep& operator=(const ScopedPointerDeep& other) {
        if (this != &other) {
            delete m_ptr;
            m_ptr = new T(*other.m_ptr);
        }
        return *this;
    }
    
    ScopedPointerDeep(ScopedPointerDeep&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    
    ScopedPointerDeep& operator=(ScopedPointerDeep&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

template <typename T>
class ScopedPointerTransfered {
public:
    explicit ScopedPointerTransfered(T* ptr = nullptr) : m_ptr(ptr) {}
    
    ~ScopedPointerTransfered() {
        delete m_ptr;
    }
    
    ScopedPointerTransfered(const ScopedPointerTransfered&) = delete;
    
    ScopedPointerTransfered& operator=(const ScopedPointerTransfered&) = delete;
    
    ScopedPointerTransfered(ScopedPointerTransfered&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    
    ScopedPointerTransfered& operator=(ScopedPointerTransfered&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

