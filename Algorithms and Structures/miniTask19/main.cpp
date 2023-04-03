#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void swap(std::vector<ListNode*>& lists, std::size_t ind1, std::size_t ind2){
    ListNode* tmp = lists[ind1];
    lists[ind1] = lists[ind2];
    lists[ind2] = tmp;
}

void balance_heap_value(std::vector<ListNode*>& lists, std::size_t ind){
    while(ind < lists.size() / 2) {

        std::size_t leave_ind1 = 2 * ind + 1;
        std::size_t leave_ind2 = 2 * ind + 2;

        if (leave_ind2 < lists.size()) {
            if (lists[ind]->val > lists[leave_ind1]->val || lists[ind]->val > lists[leave_ind2]->val) {
                std::size_t min_leave_ind = (lists[leave_ind1]->val < lists[leave_ind2]->val) ? leave_ind1 : leave_ind2;

                swap(lists, ind, min_leave_ind);
                ind = min_leave_ind;
            } else {
                break;
            }
        } else {
            if (lists[ind]->val > lists[leave_ind1]->val){
                swap(lists, ind, leave_ind1);
                ind = leave_ind1;
            } else {
                break;
            }
        }
    }
}

void heap_making(std::vector<ListNode*>& lists){
    for(long long i = lists.size() / 2 - 1; i >= 0; i--){
        balance_heap_value(lists, i);
    }
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    std::size_t i = 0;
    while(i < lists.size()){
        if (lists[i] == nullptr) {
            lists.erase(lists.begin() + i);
            i--;
        }
        i++;
    }

    if (lists.empty()){
        return nullptr;
    }

    ListNode* merged_list;
    ListNode* last_node;

    heap_making(lists);
    merged_list = lists[0];

    while (true){
        if(lists[0] == nullptr){
            last_node->next = nullptr;
            break;
        }

        last_node = lists[0];

        lists[0] = lists[0]->next;
        if (lists[0] == nullptr){
            if(lists.size() == 1){
                last_node->next = nullptr;
                break;
            } else {
                swap(lists, 0, lists.size() - 1);
                lists.pop_back();
            }
        }

        balance_heap_value(lists, 0);
        last_node->next = lists[0];
    }
    return merged_list;
}

int main() {
    auto* ln1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    auto* ln2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    auto* ln3 = new ListNode(2, new ListNode(6));

    auto* vec = new std::vector<ListNode*>();
    vec->push_back(ln1);
    vec->push_back(ln2);
    vec->push_back(ln3);

    ListNode* new_list = mergeKLists(*vec);
    ListNode* it = new_list;
    while(it != nullptr){
        std::cout << it->val << " ";
        it = it->next;
    }
    std::cout << std::endl;

}
