class Node{
    public:
        static const bool is_nonlinear = false;
        int arity;
        int index;
        Node(int, int);
        float eval();

};