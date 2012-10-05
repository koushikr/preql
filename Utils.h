/* 
 * File:   Utils.h
 * Author: anmol
 *
 * Created on 20 December, 2010, 3:33 AM
 */

#ifndef UTILS_H
#define	UTILS_H


class Utils {
public:

    Utils();

    Utils(const Utils& orig);

    virtual ~Utils();

    static void strreverse(char* begin, char* end);

    static void itoa(int value, char* str, int base);

    static void pressEnter();
private:

};

#endif	/* UTILS_H */

