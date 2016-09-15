#pragma once

#define MUTEX_BIT  0x1
#define DEAD_BIT   0x2

#include "db_malloc.h"
#include "db_object.h"
#include "db_lock.h"

typedef struct ArenaDef_ ArenaDef;
typedef struct PathStk_ PathStk;

/**
 * open/create arenas
 */

DbMap *createMap(DbMap *parent, char *name, uint32_t nameLen, uint32_t localSize, uint32_t baseSize, uint32_t objSize, uint64_t initSize, bool onDisk);
DbMap *openMap(DbMap *parent, char *name, uint32_t nameLen, ArenaDef *arena);
DbMap *arenaMap(DbMap *parent, char *name, uint32_t nameLen, PathStk *path);
void closeMap(DbMap *map);

/**
 *	map allocations
 */

uint64_t allocMap(DbMap *map, uint32_t size);
uint64_t allocBlk(DbMap *map, uint32_t size, bool zeroit);
uint64_t allocObj(DbMap *map, DbAddr *free, int type, uint32_t size, bool zeroit);
uint64_t allocObjId(DbMap *map, FreeList *list);
void *fetchObjSlot (DbMap *map, ObjId objId);
void *getObj(DbMap *map, DbAddr addr); 
void freeBlk(DbMap *map, DbAddr *addr);

uint64_t allocNode(DbMap *map, FreeList *list, int type, uint32_t size, bool zeroit);
uint64_t getNodeFromFrame (DbMap *map, DbAddr *queue);
bool getNodeWait (DbMap *map, DbAddr *queue, DbAddr *tail);
bool initObjFrame (DbMap *map, DbAddr *queue, uint32_t type, uint32_t size);
bool addSlotToFrame(DbMap *map, DbAddr *head, uint64_t addr);

void *fetchIdSlot (DbMap *map, ObjId objId);
uint64_t getFreeFrame(DbMap *map);
uint64_t allocFrame(DbMap *map);

// void *cursorNext(DbCursor *cursor, DbMap *index);
// void *cursorPrev(DbCursor *cursor, DbMap *index);

/**
 * spin latches
 */

void lockLatch(volatile char* latch);
void unlockLatch(volatile char* latch);
void waitNonZero(volatile char *zero);
void waitNonZero64(volatile uint64_t *zero);
void art_yield();

/**
 * atomic integer ops
 */

void kill_slot(volatile char* latch);

int64_t atomicAdd64(volatile int64_t *value, int64_t amt);
int32_t atomicAdd32(volatile int32_t *value, int32_t amt);
int64_t atomicOr64(volatile int64_t *value, int64_t amt);
int32_t atomicOr32(volatile int32_t *value, int32_t amt);
uint64_t compareAndSwap(uint64_t* target, uint64_t compare_val, uint64_t swap_val);

void lockArena (DbMap *map);
void unlockArena (DbMap *map);
bool fileExists(char *path);
