/*
 * ZLApplication.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLAPPLICATION_H_
#define ZLAPPLICATION_H_

#include <string>

class ZLApplicationBase {

protected:
	ZLApplicationBase(const std::string &name);
	~ZLApplicationBase();
};

class ZLApplication : public ZLApplicationBase {

protected:
	ZLApplication(const std::string &name);
	~ZLApplication();

public:
	static ZLApplication &Instance();
	static void deleteInstance();


	bool createApplication();

private:
	static ZLApplication *ourInstance;



};



#endif /* ZLAPPLICATION_H_ */
