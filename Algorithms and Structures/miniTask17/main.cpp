 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* reverseBetween(ListNode* head, int left, int right) {
    if(left == right){
        return head;
    }

    ListNode* start = head;
    for(int i = 2; i < left; i++){
        start = start->next;
    }

    if(left == 1){
        start = new ListNode();
        *start = ListNode(-1, head);
    }

    ListNode* cur_prev = start->next;
    ListNode* cur = start->next->next; 

    for(int i = left + 1; i <= right; i++){
        ListNode* tmp = cur->next;
        cur->next = cur_prev;
        cur_prev = cur;
        cur = tmp;
    }
    ListNode* tmp = start->next;
    start->next = cur_prev;
    tmp->next = cur;
    
    if(left == 1){
        head = start->next;
        delete start;
    }
    return head;
}