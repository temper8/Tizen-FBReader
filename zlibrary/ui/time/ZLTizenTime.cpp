/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
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





#include "ZLTizenTime.h"

#include "logger.h"



ZLTizenTimeManager::ZLTizenTimeManager(): ZLUnixTimeManager() {
	DBG("ZLTizenTimeManager()" );
}
/*
void ZLTizenTimeManager::OnTimerExpired(Timer& timer){
	DBG("OnTimerExpired");

	shared_ptr<ZLRunnable> task = myTasks.find(&timer)->second;
	int interval = myInterval.find(&timer)->second;
	AppLog("interval =%d",interval);
	task->run();
	timer.Start(interval);

}*/

static Eina_Bool _timer_cb(void *data EINA_UNUSED) {
	DBG("Timer expired ");
	ZLRunnable* task = (ZLRunnable*) data;
	task->run();
	return ECORE_CALLBACK_RENEW;
}

void ZLTizenTimeManager::addTask(shared_ptr<ZLRunnable> task, int interval) {
	DBG("ZLbadaTimeManager::addTask interval=%d",interval );

	removeTask(task);
	if ((interval > 0) && !task.isNull()) {
		DBG("ZLTizenTimeManager::addTask new Timer");
		Ecore_Timer *timer = ecore_timer_add((double)interval/1000.0, _timer_cb, &*task);

		myTimers[task] = timer;
		//myTasks[timer] = task;
		//myInterval[timer] = interval;
		/*
		Timer* _pTimer = new Timer;
		_pTimer->Construct(*this);
		//int id = startTimer(interval);
		myTimers[task] = _pTimer;
		myTasks[_pTimer] = task;
		myInterval[_pTimer] = interval;
		_pTimer->Start(interval);
		*/
	}

}

void ZLTizenTimeManager::removeTaskInternal(shared_ptr<ZLRunnable> task) {
	DBG("ZLTizenTimeManager::removeTaskInternal" );
	std::map<shared_ptr<ZLRunnable>,Ecore_Timer*>::iterator it = myTimers.find(task);
	if (it != myTimers.end()) {
		DBG("ZLTizenTimeManager::removeTaskInternal erase" );
		//myTasks.erase(myTasks.find(it->second));
		Ecore_Timer* timer = it->second;
	    ecore_timer_del(timer);
		myTimers.erase(it);
		//myInterval.erase(timer);
	}
}

