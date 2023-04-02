struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *detectCycle(ListNode *head) {
    if (head == nullptr){
        return nullptr;
    }

    ListNode* fastptr = head;
    ListNode* slowptr = head;
    while (slowptr != nullptr && fastptr != nullptr){
        fastptr = fastptr->next;
        if (fastptr == nullptr){
            break;
        } else {
            fastptr = fastptr->next;
        }
        slowptr = slowptr->next;
        if (fastptr == slowptr)
            break;
    }

    if (fastptr == nullptr){
        return nullptr;
    }

    fastptr = head;
    while(fastptr != slowptr){
        fastptr = fastptr->next;
        slowptr = slowptr->next;
    }
    return fastptr;
}