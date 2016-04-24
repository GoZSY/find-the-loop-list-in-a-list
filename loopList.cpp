/**************************************************************
思路一、 第一步，找环中相汇点。分别用p1，p2指向链表头部，p1每次走一步，p2每次走二步，直到p1==p2找到在环中的相汇点。
第二步，找环的入口。接上步，当p1==p2时，p2所经过节点数为2x,p1所经过节点数为x,设环中有n个节点,p2比p1多走一圈有2x=n+x; n=x;
可以看出p1实际走了一个环的步数，再让p2指向链表头部，p1位置不变，p1,p2每次走一步直到p1==p2; 此时p1指向环的入口。 
***************************************************************/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        ListNode* pfast = pHead;
        ListNode* pslow = pHead;
        if (pHead == NULL || pHead->next == NULL)
            return NULL;
         
        //找出pfast和pslow在环内相遇的位置
        while(pfast != NULL && pfast->next != NULL) {
            pslow = pslow->next;
            pfast = pfast->next->next;
            if(pslow == pfast)
                break;
        }
        if( pfast == NULL || pfast->next == NULL ) 
            return NULL; 
        pslow = pHead;
        while(true) {
            if(pslow == pfast) {
                return pfast;
            }
            pslow = pslow->next;
            pfast = pfast->next;
        }
 //       return pfast;
         
         
    }
};
/**********************************************************************************
思路二：复杂度o(n)但是会破坏链表结构
将访问过的链表断开，最后找到一个下一个节点为NULL的节点就是需要的节点

***********************************************************************************/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if (!pHead->next)
            return NULL;
        ListNode* previous = pHead;
        ListNode* front = pHead ->next;
        while (front)
        {
            previous->next = NULL;
            previous = front;
            front = front->next;
        }
        return previous;
    }
};
/****************************************************
思路三、借助vector存储访问过的节点，判断新访问的节点是否已经访问过
****************************************************/
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
		//set<int,ListNode* > val_List;
        ListNode* LoopHead = NULL;
        if(pHead == NULL)
            return LoopHead;
        vector<ListNode*> val_List;
        val_List.push_back(pHead);
        pHead = pHead -> next;
        bool ifFind = false;
        while(pHead != NULL)
        {
            val_List.push_back(pHead);
            for(int i = 0; i < val_List.size()-1; ++i)
            {
                if(val_List[i]->val == pHead->val && val_List[i]->next == pHead->next)
                {
                	LoopHead = pHead;
                    ifFind = true;
                    break;
                }
                  
            }
            if(ifFind == true)
                break;
            pHead=pHead->next;
        }
        val_List.clear();
        vector<ListNode*>(val_List).swap(val_List);
        return LoopHead;
    }
};
//还可以借助STL里的set,set不允许出现重复的节点，在插入失败时候的节点就是我们需要的节点
