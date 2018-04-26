# distutils: language=c++
import scipy.sparse
cimport numpy as np

cdef class SparseData:
    cdef readonly list rows
    cdef readonly list cols
    cdef readonly list data
    cdef readonly int nrows
    cdef readonly int width
    def __init__(self, width=None):
        self.rows = []
        self.cols = []
        self.data = []
        self.nrows = 0
        self.width = -1 if width is None else width

    def append(self, np.ndarray[np.float64_t, ndim=1] row):
        if self.width < 0:
            self.width = row.shape[0]
        cdef int i
        cdef double x
        for i in range(row.shape[0]):
            x = row[i]
            if x != 0:
                self.cols.append(i)
                self.rows.append(self.nrows)
                self.data.append(x)
        self.nrows += 1
    
    def to_csr(self):
        return scipy.sparse.csr_matrix((self.data, (self.rows, self.cols)), shape=(self.nrows, self.width))
