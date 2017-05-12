#ifndef VECTOR_H
#define	VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    /**
     * Type of vector's one cell
     */
    typedef double cell;

    /**
     * Structure represents a vector
     */
    typedef struct {
        /**
         * 1-dimensional array with values
         */
        cell* values;
        /**
         * Size of vector
         */
        int size;
        /**
         * Identification number of vector
         */
        int id;
    } vector;
    
    /**
     * Create a new vector. Values are uninitialized. Created vector is returned.
     * @param size Size of vector
     * @return 
     */
    vector* createVector(int size);
    
    /**
     * Create a new vector. Values are initialized by 0. Created vector is returned.
     * @param size Size of vector
     * @return 
     */
    vector* zeroVector(int size);
    
    /**
     * Create a "ghost" matrix with passed size. A memory for values isn't allocated. Created vector is returned.
     * @param rows Size of vector
     * @return 
     */
    vector* ghostVector(int rows);
    
    /**
     * Create a vector from double pointer with double values. It uses passed size. Created vector is returned.
     * @param values Array with values
     * @param size Size of vector
     * @return 
     */
    vector* createFromArray(cell* values, int size);
    
    /**
     * Make an occupied memory free. It prevents memory leaks.
     * @param v The passed vector
     */
    void freeVector(vector* v);
    
    /**
     * Set the given value for the passed position of the vector
     * @param v The passed vector
     * @param pos Position of a set value
     * @param value A value to set
     */
    void setVecValue(vector* v, int pos, cell value);
    
    /**
     * Return a value from the passed position of the vector
     * @param v The passed vector
     * @param pos Position of a got value
     * @return 
     */
    double getVecValue(vector* v, int pos);
    
    /**
     * Display the given vector in a console
     * @param v The passed vector
     */
    void displayVector(vector* v);
    
    /**
     * Read a vector from file with the passed filename. Read vector is returned.
     * @param filename Name of file
     * @return 
     */
    vector* readVectorFromFile(const char* filename);
    
    /**
     * Write the passed vector to a file with the passed filename
     * @param filename Name of file
     * @param v
     */
    void writeVectorToFile(const char* filename, vector* v);


#ifdef	__cplusplus
}
#endif

#endif	/* VECTOR_H */
