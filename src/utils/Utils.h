/*
 * Copyright 2019 Koushik R <rkoushik.14@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

