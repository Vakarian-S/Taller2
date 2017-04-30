    class SparseMatrix
    {
    public:
    SparseMatrix(int n);
    SparseMatrix(int rows, columns);
    
    SparseMatrix(const SparseMatrix &m);
    
    ~SparseMatrix();
    
    int getRow() const;
    int gerCol() const;
    
    
    private:
    }
