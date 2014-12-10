/*
 * ZLApplication.h
 *
 *  Created on: Dec 10, 2014
 *      Author: Alex
 */

#ifndef ZLAPPLICATION_H_
#define ZLAPPLICATION_H_
class ZLApplicationBase {

protected:
	ZLApplicationBase(const std::string &name);
	~ZLApplicationBase();
};

class ZLApplication : public ZLApplicationBase {

public:
	static ZLApplication &Instance();
	static void deleteInstance();

private:
	static ZLApplication *ourInstance;

protected:
	ZLApplication(const std::string &name);

}

class ZLApplication {
public:
	ZLApplication();
	virtual ~ZLApplication();
};

#endif /* ZLAPPLICATION_H_ */
