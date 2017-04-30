    class SparseMatrix
    {
    public:
    SparseMatrix(int n);
    SparseMatrix(int row, column);
    
    SparseMatrix(const SparseMatrix &m);
    
    ~SparseMatrix();
    
    int getRow() const;
    int gerCol() const;
    int get(int row, int column) const;
    
    
    protected:
        int m,n;
    }
