/*
LeetCode 0155. 最小栈

设计一个支持 push, pop, top 操作并能在常数时间内检索到最小元素的栈.
push(x) —— 将元素 x 推入栈中.
pop() —— 删除栈顶的元素.
top() —— 获取栈顶元素.
getMin() —— 检索栈中的最小元素.
 
示例:
输入:
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
输出:
[null,null,null,null,-3,null,0,-2]
解释:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
*/

/*
辅助栈方法
*/

class MinStack {
public:
    MinStack() {}
    
    void push(int x) {
        _data.push(x);
        if(_min.empty()){
            _min.push(x);
        }else if(x < _min.top()){
            _min.push(x);
        }else{
            _min.push(_min.top());
        }
    }
    
    void pop() {
        _data.pop();
        _min.pop();
    }
    
    int top() {
        return _data.top();
    }
    
    int getMin() {
        return _min.top();
    }
private:
    stack<int> _data;
    stack<int> _min;
};