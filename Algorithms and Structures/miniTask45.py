class PersistentNode:
    def __init__(self, value, next_node=None):
        self.value = value
        self.next = next_node


class PersistentQueueInner:
    def __init__(self, front=None, rear=None):
        self.front = front
        self.rear = rear

    def enqueue(self, value):
        new_rear = PersistentNode(value)
        if not self.rear:
            # Empty queue case
            new_front = new_rear
        else:
            self.rear.next = new_rear
            new_front = self.front
        return PersistentQueueInner(new_front, new_rear)

    def dequeue(self):
        if not self.front:
            raise IndexError("dequeue from an empty queue")
        new_front = self.front.next
        if not new_front:
            # Last element case
            new_rear = None
        else:
            new_rear = self.rear
        return PersistentQueueInner(new_front, new_rear)

    def peek(self):
        if not self.front:
            raise IndexError("peek from an empty queue")
        return self.front.value

    def is_empty(self):
        return self.front is None

    def __iter__(self):
        current = self.front
        while current:
            yield current.value
            current = current.next
            
class PersistentQueue:
    def __init__(self):
        self.history = [PersistentQueueInner()]
        
    def enqueue(self, value, version = -1):
        self.history.append(self.history[version].enqueue(value))
    
    def dequeue(self, version):
        self.history.append(self.history[version].dequeue())
    
    def peek(self, version):
        return self.history[version].peek()
    


if __name__ == "__main__":
    psq = PersistentQueue()
    psq.enqueue(1) # -> to version 1
    psq.enqueue(2, 1) # -> to version 2
    psq.enqueue(3, 2) # -> to version 3
    
    print("Peek from version 1")
    print(psq.peek(1))
    psq.dequeue(2) # -> to version 4
    
    print("Peek from version 4")
    print(psq.peek(4))
    
    print("Peek from version 2")
    print(psq.peek(2))
    
    psq.enqueue(4, 2) # -> to version 5
    
    print("Iterating version 5")
    for queue in psq.history[5]:
        print(queue)
    
