#include <unistd.h> /*getpid*/
#include <ifaddrs.h> /*ifaddrs*/
#include <string.h> /*strncpy, strcmp*/
#include <stdatomic.h> /*atomic_int*/

#include "thread_safe_uid.h" 

#define SIZEOF_IP (sizeof(((uid_t *)0)->ip))

const uid_t bad_uid = {0};

uid_t UIDCreate(void)
{
	static atomic_int atomic_counter = 0;
	uid_t uid;
	struct ifaddrs* ifaddrs;	
	uid.counter = atomic_fetch_add(&atomic_counter, 1);
	uid.time = time(NULL);
	if((time_t)-1 == uid.time)
	{
		return bad_uid;
	}

	uid.pid = getpid();

	if(getifaddrs(&ifaddrs) == -1)
	{
		return bad_uid;
	}
	
	memcpy((char*)uid.ip, ifaddrs->ifa_addr->sa_data, SIZEOF_IP);
	
	freeifaddrs(ifaddrs);
	
	return uid; 
}

int UIDIsSame(uid_t uid1, uid_t uid2)
{
	return ((uid1.time == uid2.time) && (uid1.counter == uid2.counter) 
	&& (uid1.pid == uid2.pid) && (memcmp((const char*)uid1.ip, 
	(const char*)uid2.ip, sizeof(uid1.ip)) == 0 ));
}

