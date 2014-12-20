/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ZLTYPEID_H__
#define __ZLTYPEID_H__

class ZLTypeId {

private:
	ZLTypeId();

public:
	explicit ZLTypeId(const ZLTypeId &base);

	bool operator == (const ZLTypeId &type) const;
	bool operator != (const ZLTypeId &type) const;
	bool isSubtypeOf(const ZLTypeId &type) const;

private:
	const ZLTypeId *myBase;	

friend class ZLObjectWithRTTI;
};

class ZLObjectWithRTTI {

public:
	static const ZLTypeId TYPE_ID;

public:
	virtual ~ZLObjectWithRTTI();
	bool isInstanceOf(const ZLTypeId &type, bool exact = false) const;

protected:
	virtual const ZLTypeId &typeId() const = 0;
};

template <typename T>
T zlobject_cast(ZLObjectWithRTTI *object) {
	if (!object || !object->isInstanceOf(reinterpret_cast<T>(0)->TYPE_ID))
		return 0;
	return static_cast<T>(object);
}

template <typename T>
T zlobject_cast(const ZLObjectWithRTTI *object) {
	if (!object || !object->isInstanceOf(reinterpret_cast<T>(0)->TYPE_ID))
		return 0;
	return static_cast<T>(object);
}


inline bool ZLTypeId::operator == (const ZLTypeId &type) const {
	return this == &type;
}

inline bool ZLTypeId::operator != (const ZLTypeId &type) const {
	return this != &type;
}

inline ZLObjectWithRTTI::~ZLObjectWithRTTI() {
}

#endif /* __ZLTYPEID_H__ */
