/*
 * hp-tcpSocket.cpp -- HP-Socket 6.0.9, TCP components only, amalgamated.
 *
 * Companion translation unit for hp-tcpSocket.h. Add both files to your
 * Visual Studio project; nothing else from HP-Socket is needed.
 *
 * Derived from HP-Socket 6.0.9 (Windows) by Bruce Liang (ldcsaa).
 *   https://github.com/ldcsaa/HP-Socket
 * Licensed under the Apache License, Version 2.0.
 */

#include "hp-tcpSocket.h"


/* ========================================================================== */
/*  SysHelper.cpp
/*  source: Windows\Src\Common\SysHelper.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "SysHelper.h" */
/* [amalgamated] #include "GeneralHelper.h" */

///////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD GetDefaultWorkerThreadCount()
{
	static const DWORD s_dwtc = min((::SysGetNumberOfProcessors() * 2 + 2), MAX_WORKER_THREAD_COUNT);
	return s_dwtc;
}

DWORD GetSysPageSize()
{
	static const DWORD s_dtsbs = ::SysGetPageSize();
	return s_dtsbs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

VOID SysGetSystemInfo(LPSYSTEM_INFO pInfo)
{
	ASSERT(pInfo != nullptr);
	::GetNativeSystemInfo(pInfo);
}

DWORD SysGetNumberOfProcessors()
{
	SYSTEM_INFO si;
	SysGetSystemInfo(&si);
	
	return si.dwNumberOfProcessors;
}

DWORD SysGetPageSize()
{
	SYSTEM_INFO si;
	SysGetSystemInfo(&si);

	return si.dwPageSize;
}


/* ========================================================================== */
/*  FuncHelper.cpp
/*  source: Windows\Src\Common\FuncHelper.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "SysHelper.h" */
/* [amalgamated] #include "FuncHelper.h" */

void __EXIT_FN_(void (*fn)(int), LPCSTR lpszFnName, int* lpiExitCode, int iErrno, LPCSTR lpszFile, int iLine, LPCSTR lpszFunc, LPCSTR lpszTitle)
{
	if(iErrno >= 0)
		SetLastError(iErrno);
	else
		iErrno = GetLastError();

	if(!lpszTitle)
	{
		lpszTitle = CreateLocalObjects(char, 50);

		if(lpiExitCode)
			sprintf((LPSTR)lpszTitle, "(#%d, %u) > %s(%d) [%d]", SELF_PROCESS_ID, SELF_THREAD_ID, lpszFnName, *lpiExitCode, iErrno);
		else
			sprintf((LPSTR)lpszTitle, "(#%d, %u) > %s() [%d]", SELF_PROCESS_ID, SELF_THREAD_ID, lpszFnName, iErrno);
	}

	if(lpszFile && iLine > 0)
		FPRINTLN(stderr, "%s : %s\n  => %s (%d) : %s", lpszTitle, strerror(iErrno), lpszFile, iLine, lpszFunc ? lpszFunc : "");
	else
		FPRINTLN(stderr, "%s : %s", lpszTitle, strerror(iErrno));

	if(lpiExitCode)
		fn(*lpiExitCode);
	else
		((void (*)())fn)();
}

void EXIT(int iExitCode, int iErrno, LPCSTR lpszFile, int iLine, LPCSTR lpszFunc, LPCSTR lpszTitle)
{
	__EXIT_FN_(exit, "exit", &iExitCode, iErrno, lpszFile, iLine, lpszFunc, lpszTitle);
}

void _EXIT(int iExitCode, int iErrno, LPCSTR lpszFile, int iLine, LPCSTR lpszFunc, LPCSTR lpszTitle)
{
	__EXIT_FN_(_exit, "_exit", &iExitCode, iErrno, lpszFile, iLine, lpszFunc, lpszTitle);
}

void ABORT(int iErrno, LPCSTR lpszFile, int iLine, LPCSTR lpszFunc, LPCSTR lpszTitle)
{
	__EXIT_FN_((void (*)(int))abort, "abort", nullptr, iErrno, lpszFile, iLine, lpszFunc, lpszTitle);
}

BOOL SetSequenceThreadName(HANDLE hThread, LPCTSTR lpszPrefix, volatile UINT& vuiSeq)
{
#if _WIN32_WINNT < _WIN32_WINNT_WIN10
	::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return FALSE;
#else
	UINT uiSequence = ::InterlockedIncrement(&vuiSeq);
	return SetThreadName(hThread, lpszPrefix, uiSequence);
#endif
}

BOOL SetThreadName(HANDLE hThread, LPCTSTR lpszPrefix, UINT uiSequence)
{
	CString strName;
	strName.Format(_T("%s%u"), lpszPrefix, uiSequence);

	ASSERT(strName.GetLength() < MAX_PATH);

	return SetThreadName(hThread, strName);
}

BOOL SetThreadName(HANDLE hThread, LPCTSTR lpszName)
{
#if _WIN32_WINNT < _WIN32_WINNT_WIN10
	::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return FALSE;
#else
	if(hThread == nullptr)
		hThread = SELF_THREAD;

	return SUCCEEDED(::SetThreadDescription(hThread, CT2W(lpszName)));
#endif
}


/* ========================================================================== */
/*  WaitFor.cpp
/*  source: Windows\Src\Common\WaitFor.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "WaitFor.h" */
/* [amalgamated] #include "GeneralHelper.h" */
/* [amalgamated] #include "CriticalSection.h" */

#include <MmSystem.h>
#pragma comment(lib, "Winmm")

static CEvt _s_evWait;

DWORD TimeGetTime()
{
	return ::timeGetTime();
}

DWORD GetTimeGap32(DWORD dwOriginal, DWORD dwCurrent)
{
	if(dwCurrent == 0)
		dwCurrent = ::timeGetTime();

	return dwCurrent - dwOriginal;
}

#if _WIN32_WINNT >= _WIN32_WINNT_WS08
ULONGLONG GetTimeGap64(ULONGLONG ullOriginal, ULONGLONG ullCurrent)
{
	if(ullCurrent == 0)
		ullCurrent = ::GetTickCount64();

	return ullCurrent - ullOriginal;
}
#endif

BOOL PeekMessageLoop(BOOL bDispatchQuitMsg)
{
	BOOL value = TRUE;

	MSG msg;
	while(::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if(msg.message == WM_QUIT && !bDispatchQuitMsg)
		{
			value = FALSE;
			break;
		}

		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return value;
}

DWORD WaitForMultipleObjectsWithMessageLoop(DWORD dwHandles, HANDLE szHandles[], DWORD dwMilliseconds, BOOL bWaitAll, DWORD dwWakeMask)
{
	DWORD dwResult		= WAIT_FAILED;
	DWORD dwBeginTime	= (dwMilliseconds == INFINITE) ? INFINITE : ::timeGetTime();

	while(TRUE)
	{
		int iWaitTime;
		if(dwBeginTime == INFINITE)
			iWaitTime	= INFINITE;
		else
		{
			iWaitTime	= dwMilliseconds - (GetTimeGap32(dwBeginTime));

			if(iWaitTime <= 0)
			{
				dwResult = WAIT_TIMEOUT;
				break;
			}
		}

		dwResult = ::MsgWaitForMultipleObjects(dwHandles, szHandles, bWaitAll, (DWORD)iWaitTime, dwWakeMask);

		if(dwResult == (WAIT_OBJECT_0 + dwHandles))
			PeekMessageLoop();
		else
			break;
	}

	return dwResult;
}

BOOL MsgWaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds, BOOL bWaitAll, DWORD dwWakeMask)
{
	DWORD dwResult = WaitForMultipleObjectsWithMessageLoop(1, &hHandle, dwMilliseconds, bWaitAll, dwWakeMask);

	switch(dwResult)
	{
	case WAIT_OBJECT_0:
		return TRUE;
	case WAIT_TIMEOUT:
		::SetLastError(ERROR_TIMEOUT);
		return FALSE;
	case WAIT_FAILED:
		return FALSE;
	default:
		ENSURE(FALSE);
	}

	return FALSE;
}

BOOL WaitFor(DWORD dwMilliseconds)
{
	if(dwMilliseconds == 0)
		::Sleep(0);
	else
		return (::WaitForSingleObject(_s_evWait, dwMilliseconds) == WAIT_TIMEOUT);

	return TRUE;
}

BOOL WaitWithMessageLoop(DWORD dwMilliseconds, DWORD dwWakeMask)
{
	if(dwMilliseconds == 0)
		::Sleep(0);
	else
		return (MsgWaitForSingleObject(_s_evWait, dwMilliseconds, FALSE, dwWakeMask) == FALSE);

	return TRUE;
}

void WaitForWorkingQueue(long* plWorkingItemCount, long lMaxWorkingItemCount, DWORD dwCheckInterval)
{
	while(*plWorkingItemCount > lMaxWorkingItemCount)
		WaitFor(dwCheckInterval);
}

void WaitForComplete(long* plWorkingItemCount, DWORD dwCheckInterval)
{
	WaitForWorkingQueue(plWorkingItemCount, 0, dwCheckInterval);
}

void MsgWaitForWorkingQueue(long* plWorkingItemCount, long lMaxWorkingItemCount, DWORD dwCheckInterval)
{
	while(*plWorkingItemCount > lMaxWorkingItemCount)
		WaitWithMessageLoop(dwCheckInterval);
}

void MsgWaitForComplete(long* plWorkingItemCount, DWORD dwCheckInterval)
{
	MsgWaitForWorkingQueue(plWorkingItemCount, 0, dwCheckInterval);
}

CTimePeriod::CTimePeriod(UINT uiPeriod)
{
	TIMECAPS tc;

	if(::timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
		m_uiPeriod = 0;
	else
	{
		m_uiPeriod = min(max(tc.wPeriodMin, uiPeriod), tc.wPeriodMax);
		::timeBeginPeriod(m_uiPeriod);
	}
}

CTimePeriod::~CTimePeriod()
{
	if(IsValid())
		::timeEndPeriod(m_uiPeriod);
}


/* ========================================================================== */
/*  BufferPool.cpp
/*  source: Windows\Src\Common\BufferPool.cpp
/* ========================================================================== */

/******************************************************************************
Module:  BufferPool.cpp
Notices: Copyright (c) 2013 Bruce Liang
Purpose: 򵦄ڴ滺崘
Desc:
******************************************************************************/

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "BufferPool.h" */
/* [amalgamated] #include "WaitFor.h" */

#pragma warning(push)
#pragma warning(disable: 4458)

const DWORD TItem::DEFAULT_ITEM_CAPACITY			= DEFAULT_BUFFER_CACHE_CAPACITY;
const DWORD CBufferPool::DEFAULT_MAX_CACHE_SIZE		= 0;
const DWORD CBufferPool::DEFAULT_ITEM_CAPACITY		= CItemPool::DEFAULT_ITEM_CAPACITY;
const DWORD CBufferPool::DEFAULT_ITEM_POOL_SIZE		= CItemPool::DEFAULT_POOL_SIZE;
const DWORD CBufferPool::DEFAULT_ITEM_POOL_HOLD		= CItemPool::DEFAULT_POOL_HOLD;
const DWORD CBufferPool::DEFAULT_BUFFER_LOCK_TIME	= DEFAULT_OBJECT_CACHE_LOCK_TIME;
const DWORD CBufferPool::DEFAULT_BUFFER_POOL_SIZE	= DEFAULT_OBJECT_CACHE_POOL_SIZE;
const DWORD CBufferPool::DEFAULT_BUFFER_POOL_HOLD	= DEFAULT_OBJECT_CACHE_POOL_HOLD;

TItem* TItem::Construct(CPrivateHeap& heap, int capacity, BYTE* pData, int length)
{
	ASSERT(capacity > 0);

	int item_size	= sizeof(TItem);
	TItem* pItem	= (TItem*)heap.Alloc(item_size + capacity);
	BYTE* pHead		= (BYTE*)pItem + item_size;

	pItem->TItem::TItem(heap, pHead, capacity, pData, length);

	return pItem;
}

void TItem::Destruct(TItem* pItem)
{
	ASSERT(pItem != nullptr);

	CPrivateHeap& heap = pItem->GetPrivateHeap();
	pItem->TItem::~TItem();
	heap.Free(pItem);
}

int TItem::Cat(const BYTE* pData, int length)
{
	ASSERT(pData != nullptr && length >= 0);

	int cat = min(Remain(), length);

	if(cat > 0)
	{
		memcpy(end, pData, cat);
		end += cat;
	}

	return cat;
}

int TItem::Cat(const TItem& other)
{
	ASSERT(this != &other);
	return Cat(other.Ptr(), other.Size());
}

int TItem::Fetch(BYTE* pData, int length)
{
	ASSERT(pData != nullptr && length > 0);

	int fetch = min(Size(), length);
	memcpy(pData, begin, fetch);
	begin	 += fetch;

	return fetch;
}

int TItem::Peek(BYTE* pData, int length)
{
	ASSERT(pData != nullptr && length > 0);

	int peek = min(Size(), length);
	memcpy(pData, begin, peek);

	return peek;
}

int TItem::Increase(int length)
{
	ASSERT(length >= 0);

	int increase = min(Remain(), length);
	end			+= increase;

	return increase;
}

int TItem::Reduce(int length)
{
	ASSERT(length >= 0);

	int reduce   = min(Size(), length);
	begin		+= reduce;

	return reduce;
}

void	TItem::Reset(int first, int last)
{
	ASSERT(first >= -1 && first <= capacity);
	ASSERT(last >= -1 && last <= capacity);

	if(first >= 0)	begin	= head + min(first, capacity);
	if(last >= 0)	end		= head + min(last, capacity);
}

TBuffer* TBuffer::Construct(CBufferPool& pool, ULONG_PTR dwID)
{
	ASSERT(dwID != 0);

	CPrivateHeap& heap	= pool.GetPrivateHeap();
	TBuffer* pBuffer	= (TBuffer*)heap.Alloc(sizeof(TBuffer));

	pBuffer->TBuffer::TBuffer(heap, pool.GetItemPool(), dwID);

	return pBuffer;
}

void TBuffer::Destruct(TBuffer* pBuffer)
{
	ASSERT(pBuffer != nullptr);

	CPrivateHeap& heap = pBuffer->heap;
	pBuffer->TBuffer::~TBuffer();
	heap.Free(pBuffer);
}

void TBuffer::Reset()
{
	id		 = 0;
	length	 = 0;
	freeTime = ::TimeGetTime();
}

int TBuffer::Cat(const BYTE* pData, int len)
{
	items.Cat(pData, len);
	return IncreaseLength(len);
}

int TBuffer::Cat(const TItem* pItem)
{
	items.Cat(pItem);
	return IncreaseLength(pItem->Size());
}

int TBuffer::Cat(const TItemList& other)
{
	ASSERT(&items != &other);

	for(TItem* pItem = other.Front(); pItem != nullptr; pItem = pItem->next)
		Cat(pItem);

	return length;
}

int TBuffer::Fetch(BYTE* pData, int len)
{
	int fetch = items.Fetch(pData, len);
	DecreaseLength(fetch);

	return fetch;
}

int TBuffer::Peek(BYTE* pData, int len)
{
	return items.Peek(pData, len);
}

int TBuffer::Reduce(int len)
{
	int reduce = items.Reduce(len);
	DecreaseLength(reduce);

	return reduce;
}

void CBufferPool::PutFreeBuffer(ULONG_PTR dwID)
{
	ASSERT(dwID != 0);

	TBuffer* pBuffer = FindCacheBuffer(dwID);

	if(pBuffer != nullptr)
		PutFreeBuffer(pBuffer);
}

void CBufferPool::PutFreeBuffer(TBuffer* pBuffer)
{
	ASSERT(pBuffer != nullptr);

	if(!pBuffer->IsValid())
		return;

	m_bfCache.RemoveEx(pBuffer->ID());

	BOOL bOK = FALSE;

	{
		CCriSecLock locallock(pBuffer->cs);

		if(pBuffer->IsValid())
		{
			pBuffer->Reset();
			bOK = TRUE;
		}
	}

	if(bOK)
	{
		m_itPool.PutFreeItem(pBuffer->items);

#ifndef USE_EXTERNAL_GC
		ReleaseGCBuffer();
#endif
		if(!m_lsFreeBuffer.TryPut(pBuffer))
			m_lsGCBuffer.PushBack(pBuffer);
	}
}

void CBufferPool::ReleaseGCBuffer(BOOL bForce)
{
	::ReleaseGCObj(m_lsGCBuffer, m_dwBufferLockTime, bForce);
}

TBuffer* CBufferPool::PutCacheBuffer(ULONG_PTR dwID)
{
	ASSERT(dwID != 0);

	TBuffer* pBuffer = PickFreeBuffer(dwID);
	m_bfCache.SetEx(dwID, pBuffer);

	return pBuffer;
}

TBuffer* CBufferPool::PickFreeBuffer(ULONG_PTR dwID)
{
	ASSERT( dwID != 0);

	DWORD dwIndex;
	TBuffer* pBuffer = nullptr;

	if(m_lsFreeBuffer.TryLock(&pBuffer, dwIndex))
	{
		if(::GetTimeGap32(pBuffer->freeTime) >= m_dwBufferLockTime)
			ENSURE(m_lsFreeBuffer.ReleaseLock(nullptr, dwIndex));
		else
		{
			ENSURE(m_lsFreeBuffer.ReleaseLock(pBuffer, dwIndex));
			pBuffer = nullptr;
		}
	}

	if(pBuffer)	pBuffer->id	= dwID;
	else		pBuffer		= TBuffer::Construct(*this, dwID);

	ASSERT(pBuffer);
	return pBuffer;
}

TBuffer* CBufferPool::FindCacheBuffer(ULONG_PTR dwID)
{
	ASSERT(dwID != 0);

	TBuffer* pBuffer = nullptr;

	if(m_bfCache.GetEx(dwID, &pBuffer) != TBufferCache::GR_VALID)
		pBuffer = nullptr;

	return pBuffer;
}

void CBufferPool::Prepare()
{
	m_itPool.Prepare();

	m_bfCache.Reset(m_dwMaxCacheSize);
	m_lsFreeBuffer.Reset(m_dwBufferPoolSize);
}

void CBufferPool::Clear()
{
	TBufferCache::IndexSet& indexes = m_bfCache.Indexes();

	for(auto it = indexes.begin(), end = indexes.end(); it != end; ++it)
	{
		TBuffer* pBuffer = FindCacheBuffer(*it);
		if(pBuffer) TBuffer::Destruct(pBuffer);
	}

	m_bfCache.Reset();

	m_lsFreeBuffer.Clear();

	ReleaseGCBuffer(TRUE);
	ENSURE(m_lsGCBuffer.IsEmpty());

	m_itPool.Clear();
	m_heap.Reset();
}

#pragma warning(pop)


/* ========================================================================== */
/*  RWLock.cpp
/*  source: Windows\Src\Common\RWLock.cpp
/* ========================================================================== */

/* [amalgamated] #include "StdAfx.h" */
/* [amalgamated] #include "RWLock.h" */

////////////////////////////////// CSWMR Functions ////////////////////////////////////

CSWMR::CSWMR()
: m_smRead			(MAXLONG)
, m_smWrite			(1)
, m_nWaitingReaders	(0)
, m_nWaitingWriters	(0)
, m_nActive			(0)
{

}

CSWMR::~CSWMR()
{
	ASSERT(m_nWaitingReaders == 0);
	ASSERT(m_nWaitingWriters == 0);
	ASSERT(m_nActive		 == 0);
}

VOID CSWMR::WaitToRead()
{
	BOOL fResourceWritePending;

	{
		CSpinLock locallock(m_cs);

		fResourceWritePending = (m_nWaitingWriters || (m_nActive < 0));

		if(fResourceWritePending)
			++m_nWaitingReaders;
		else
			++m_nActive;
	}

	if(fResourceWritePending)
		m_smRead.Wait();
}

VOID CSWMR::WaitToWrite()
{
	BOOL fResourceOwned;

	{
		CSpinLock locallock(m_cs);

		fResourceOwned = (m_nActive != 0);

		if(fResourceOwned)
			++m_nWaitingWriters;
		else
			m_nActive = -1;
	}

	if(fResourceOwned)
		m_smWrite.Wait();
}

VOID CSWMR::Done()
{
	CSEM* pSem  = nullptr;
	LONG lCount = 1;

	{
		CSpinLock locallock(m_cs);

		if(m_nActive > 0)
			--m_nActive;
		else
			++m_nActive;

		if(m_nActive == 0)
		{
			if(m_nWaitingWriters > 0)
			{
				m_nActive = -1;
				--m_nWaitingWriters;
				pSem = &m_smWrite;
			}
			else if(m_nWaitingReaders > 0)
			{
				m_nActive = m_nWaitingReaders;
				m_nWaitingReaders = 0;
				pSem = &m_smRead;
				lCount = m_nActive;
			}
		}
	}

	if(pSem != nullptr)
		pSem->Release(lCount);
}

//////////////////////////////// CRWLock Functions //////////////////////////////////

#if _WIN32_WINNT >= _WIN32_WINNT_WS08

CSlimRWLock::CSlimRWLock()
	: m_nActive			(0)
	, m_dwWriterTID		(0)
{

}

CSlimRWLock::~CSlimRWLock()
{
	ASSERT(m_nActive	 == 0);
	ASSERT(m_dwWriterTID == 0);
}

VOID CSlimRWLock::WaitToRead()
{
	BOOL bWait = FALSE;

	{
		CSpinLock locallock(m_cs);

		if(m_nActive > 0)
			++m_nActive;
		else if(m_nActive == 0)
		{
			if(m_smLock.TryWaitToRead())
				++m_nActive;
			else
				bWait = TRUE;
		}
		else if(!IsOwner())
			bWait = TRUE;
	}

	if(bWait)
	{
		m_smLock.WaitToRead();

		CSpinLock locallock(m_cs);
		++m_nActive;
	}
}

VOID CSlimRWLock::WaitToWrite()
{
	BOOL bWait = FALSE;

	{
		CSpinLock locallock(m_cs);

		if(m_nActive > 0)
			bWait = TRUE;
		else if(m_nActive == 0)
		{
			if(m_smLock.TryWaitToWrite())
			{
				SetOwner();
				--m_nActive;
			}
			else
				bWait = TRUE;
		}
		else
		{
			if(IsOwner())
				--m_nActive;
			else
				bWait = TRUE;
		}
	}

	if(bWait)
	{
		m_smLock.WaitToWrite();

		SetOwner();
		--m_nActive;
	}
}

VOID CSlimRWLock::ReadDone()
{
	ASSERT(m_nActive != 0);

	if(m_nActive > 0)
	{
		{
			CSpinLock locallock(m_cs);
			--m_nActive;
		}

		m_smLock.ReadDone();
	}
	else
		ASSERT(IsOwner());
}

VOID CSlimRWLock::WriteDone()
{
	ASSERT(IsOwner());
	ASSERT(m_nActive < 0);

	BOOL bDone;

	{
		CSpinLock locallock(m_cs);
		bDone = (++m_nActive == 0);
	}

	if(bDone)
	{
		DetachOwner();
		m_smLock.WriteDone();
	}
	else
		ASSERT(IsOwner());
}

#endif

CSEMRWLock::CSEMRWLock()
: m_smRead			(MAXLONG)
, m_smWrite			(1)
, m_nWaitingReaders	(0)
, m_nWaitingWriters	(0)
, m_nActive			(0)
, m_dwWriterTID		(0)
{

}

CSEMRWLock::~CSEMRWLock()
{
	ASSERT(m_nActive	 == 0);
	ASSERT(m_dwWriterTID == 0);
}

VOID CSEMRWLock::WaitToRead()
{
	BOOL bWait = FALSE;

	{
		CSpinLock locallock(m_cs);

		if(m_nActive > 0)
			++m_nActive;
		else if(m_nActive == 0)
		{
			if(m_nWaitingWriters == 0)
				++m_nActive;
			else
			{
				++m_nWaitingReaders;
				bWait = TRUE;
			}
		}
		else
		{
			if(!IsOwner())
			{
				++m_nWaitingReaders;
				bWait = TRUE;
			}
		}
	}

	if(bWait)
	{
		m_smRead.Wait();
	}
}

VOID CSEMRWLock::WaitToWrite()
{
	BOOL bWait = FALSE;

	{
		CSpinLock locallock(m_cs);

		if(m_nActive > 0)
		{
			++m_nWaitingWriters;
			bWait = TRUE;
		}
		else if(m_nActive == 0)
		{
			--m_nActive;
			SetOwner();
		}
		else
		{
			if(IsOwner())
				--m_nActive;
			else
			{
				++m_nWaitingWriters;
				bWait = TRUE;
			}
		}
	}

	if(bWait)
	{
		m_smWrite.Wait();
		SetOwner();
	}
}

VOID CSEMRWLock::ReadDone()
{
	CSEM* pSem	 = nullptr;
	LONG  lCount = 0;

	ASSERT(m_nActive != 0);

	if(m_nActive > 0)
	{
		CSpinLock locallock(m_cs);

		if(--m_nActive == 0)
			Done(&pSem, lCount);
	}
	else
		ASSERT(IsOwner());

	if(pSem != nullptr)
		pSem->Release(lCount);
}

VOID CSEMRWLock::WriteDone()
{
	CSEM* pSem	 = nullptr;
	LONG  lCount = 0;

	{
		ASSERT(m_nActive < 0);

		CSpinLock locallock(m_cs);

		if(++m_nActive == 0)
		{
			DetachOwner();
			Done(&pSem, lCount);
		}
		else
			ASSERT(IsOwner());
	}

	if(pSem != nullptr)
		pSem->Release(lCount);
}

VOID CSEMRWLock::Done(CSEM** ppSem, LONG& lCount)
{
	ASSERT(m_nActive	 == 0);
	ASSERT(m_dwWriterTID == 0);

	if(m_nWaitingWriters > 0)
	{
		--m_nActive;
		--m_nWaitingWriters;

		lCount = 1;
		*ppSem = &m_smWrite;
	}
	else if(m_nWaitingReaders > 0)
	{
		m_nActive			= m_nWaitingReaders;
		m_nWaitingReaders	= 0;
		lCount				= m_nActive;
		*ppSem				= &m_smRead;
	}
}

/////////////////////////////////// End of File /////////////////////////////////////


/* ========================================================================== */
/*  SocketHelper.cpp
/*  source: Windows\Src\SocketHelper.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "Common/GeneralHelper.h" */
/* [amalgamated] #include "Common/SysHelper.h" */
/* [amalgamated] #include "SocketHelper.h" */

#include <mstcpip.h>
#pragma comment(lib, "ws2_32")

#if !defined(stscanf_s)
	#ifdef _UNICODE
		#define stscanf_s	swscanf_s
	#else
		#define stscanf_s	sscanf_s
	#endif
#endif

static const BYTE s_szUdpCloseNotify[] = {0xBE, 0xB6, 0x1F, 0xEB, 0xDA, 0x52, 0x46, 0xBA, 0x92, 0x33, 0x59, 0xDB, 0xBF, 0xE6, 0xC8, 0xE4};
static const int s_iUdpCloseNotifySize = ARRAY_SIZE(s_szUdpCloseNotify);

const hp_addr hp_addr::ANY_ADDR4(AF_INET, TRUE);
const hp_addr hp_addr::ANY_ADDR6(AF_INET6, TRUE);

///////////////////////////////////////////////////////////////////////////////////////////////////////

ADDRESS_FAMILY DetermineAddrFamily(LPCTSTR lpszAddress)
{
	if (!lpszAddress || lpszAddress[0] == 0)
		return AF_UNSPEC;

	if(::StrChr(lpszAddress, IPV6_ADDR_SEPARATOR_CHAR))
		return AF_INET6;

	TCHAR c;
	int arr[4];

	if(stscanf_s(lpszAddress, _T("%d.%d.%d.%d%c"), &arr[0], &arr[1], &arr[2], &arr[3], &c, 1) != 4)
		return AF_UNSPEC;

	for(int i = 0; i < 4; i++)
	{
		if(arr[i] < 0 || arr[i] > 255)
			return AF_UNSPEC;
	}

	return AF_INET;
}

BOOL GetInAddr(LPCTSTR lpszAddress, HP_ADDR& addr)
{
	addr.family = DetermineAddrFamily(lpszAddress);

	if (addr.family == AF_UNSPEC)
		return FALSE;

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
	return (::InetPton(addr.family, lpszAddress, addr.Addr()) == TRUE);
#else
	HP_SOCKADDR sockAddr(addr.family);

	if(!GetSockAddr(lpszAddress, 0, sockAddr))
		return FALSE;

	memcpy(addr.Addr(), sockAddr.SinAddr(), addr.AddrSize());

	return TRUE;
#endif
}

BOOL GetSockAddr(LPCTSTR lpszAddress, USHORT usPort, HP_SOCKADDR& addr)
{
	if(addr.family != AF_INET && addr.family != AF_INET6)
	{
		::WSASetLastError(WSAEADDRNOTAVAIL);
		return FALSE;
	}

	int iSize = addr.AddrSize();

	if(::WSAStringToAddress((LPTSTR)lpszAddress, addr.family, nullptr, addr.Addr(), &iSize) != NO_ERROR)
		return FALSE;

	if(usPort != 0)
		addr.SetPort(usPort);

	return TRUE;
}

BOOL IsIPAddress(LPCTSTR lpszAddress, EnIPAddrType* penType)
{
	HP_ADDR addr;

	BOOL isOK = GetInAddr(lpszAddress, addr);

	if(isOK && penType)
		*penType = addr.IsIPv4() ? IPT_IPV4 : IPT_IPV6;

	return isOK;
}

BOOL GetIPAddress(LPCTSTR lpszHost, LPTSTR lpszIP, int& iIPLen, EnIPAddrType& enType)
{
	HP_SOCKADDR addr;

	if(!GetSockAddrByHostName(lpszHost, 0, addr))
		return FALSE;

	enType = addr.IsIPv4() ? IPT_IPV4 : IPT_IPV6;

	USHORT usPort;
	ADDRESS_FAMILY usFamily;
	return sockaddr_IN_2_A(addr, usFamily, lpszIP, iIPLen, usPort);
}

BOOL GetSockAddrByHostName(LPCTSTR lpszHost, USHORT usPort, HP_SOCKADDR& addr, ADDRESS_FAMILY af)
{
	addr.family = DetermineAddrFamily(lpszHost);

	if(addr.family == AF_UNSPEC)
	{
		addr.family = af;
		return GetSockAddrByHostNameDirectly(lpszHost, usPort, addr);
	}

	if(addr.family != af && af != AF_UNSPEC)
	{
		::WSASetLastError(WSAEAFNOSUPPORT);
		return FALSE;
	}

	return GetSockAddr(lpszHost, usPort, addr);
}

BOOL GetSockAddrByHostNameDirectly(LPCTSTR lpszHost, USHORT usPort, HP_SOCKADDR& addr)
{
	addr.ZeroAddr();

	addrinfo* pInfo	= nullptr;
	addrinfo hints	= {0};

	hints.ai_flags	= (AI_V4MAPPED | AI_ADDRCONFIG);
	hints.ai_family	= addr.family;

	int rs = ::getaddrinfo(CT2A(lpszHost), nullptr, &hints, &pInfo);

	if(rs != NO_ERROR)
	{
		::WSASetLastError(rs);
		return FALSE;
	}

	BOOL isOK = FALSE;

	for(addrinfo* pCur = pInfo; pCur != nullptr; pCur = pCur->ai_next)
	{
		if(pCur->ai_family == AF_INET || pCur->ai_family == AF_INET6)
		{
			memcpy(addr.Addr(), pCur->ai_addr, pCur->ai_addrlen);
			isOK = TRUE;

			break;
		}
	}

	::freeaddrinfo(pInfo);

	if(isOK)
		addr.SetPort(usPort);
	else
		::WSASetLastError(WSAHOST_NOT_FOUND);

	return isOK;
}

BOOL EnumHostIPAddresses(LPCTSTR lpszHost, EnIPAddrType enType, LPTIPAddr** lpppIPAddr, int& iIPAddrCount)
{
	*lpppIPAddr	 = nullptr;
	iIPAddrCount = 0;

	ADDRESS_FAMILY usFamily =	(enType == IPT_ALL					?
								AF_UNSPEC	: (enType == IPT_IPV4	?
								AF_INET		: (enType == IPT_IPV6	?
								AF_INET6	: 0xFF)));
	
	if(usFamily == 0xFF)
	{
		::WSASetLastError(WSAEAFNOSUPPORT);
		return FALSE;
	}

	vector<HP_PSOCKADDR> vt;

	ADDRESS_FAMILY usFamily2 = DetermineAddrFamily(lpszHost);

	if(usFamily2 != AF_UNSPEC)
	{
		if(usFamily != AF_UNSPEC && usFamily != usFamily2)
		{
			::WSASetLastError(WSAHOST_NOT_FOUND);
			return FALSE;
		}

		HP_SOCKADDR addr(usFamily2);

		if(!GetSockAddr(lpszHost, 0, addr))
			return FALSE;

		vt.emplace_back(&addr);

		return RetrieveSockAddrIPAddresses(vt, lpppIPAddr, iIPAddrCount);
	}

	addrinfo* pInfo	= nullptr;
	addrinfo hints	= {0};

	hints.ai_flags	= AI_ALL;
	hints.ai_family	= usFamily;

	int rs = ::getaddrinfo(CT2A(lpszHost), nullptr, &hints, &pInfo);

	if(rs != NO_ERROR)
	{
		::WSASetLastError(rs);
		return FALSE;
	}

	for(addrinfo* pCur = pInfo; pCur != nullptr; pCur = pCur->ai_next)
	{
		if(pCur->ai_family == AF_INET || pCur->ai_family == AF_INET6)
			vt.emplace_back((HP_PSOCKADDR)pCur->ai_addr);
	}

	BOOL isOK = RetrieveSockAddrIPAddresses(vt, lpppIPAddr, iIPAddrCount);

	::freeaddrinfo(pInfo);

	if(!isOK) ::WSASetLastError(WSAHOST_NOT_FOUND);

	return isOK;
}

BOOL RetrieveSockAddrIPAddresses(const vector<HP_PSOCKADDR>& vt, LPTIPAddr** lpppIPAddr, int& iIPAddrCount)
{
	iIPAddrCount = (int)vt.size();

	if(iIPAddrCount == 0) return FALSE;

	HP_PSOCKADDR	pSockAddr;
	ADDRESS_FAMILY	usFamily;
	USHORT			usPort;
	int				iAddrLength;
	LPTSTR			lpszAddr;
	LPTIPAddr		lpItem;

	(*lpppIPAddr) = new LPTIPAddr[iIPAddrCount + 1];
	(*lpppIPAddr)[iIPAddrCount] = nullptr;

	for(int i = 0; i < iIPAddrCount; i++)
	{
		pSockAddr	= vt[i];
		iAddrLength	= HP_SOCKADDR::AddrMinStrLength(pSockAddr->family);
		lpszAddr	= new TCHAR[iAddrLength];

		ENSURE(sockaddr_IN_2_A(*vt[i], usFamily, lpszAddr, iAddrLength, usPort));

		lpItem			= new TIPAddr;
		lpItem->type	= pSockAddr->IsIPv4() ? IPT_IPV4 : IPT_IPV6;
		lpItem->address	= lpszAddr;

		(*lpppIPAddr)[i] = lpItem;
	}

	return TRUE;
}

BOOL FreeHostIPAddresses(LPTIPAddr* lppIPAddr)
{
	if(!lppIPAddr) return FALSE;

	LPTIPAddr p;
	LPTIPAddr* lppCur = lppIPAddr;

	while((p = *lppCur++) != nullptr)
	{
		delete[] p->address;
		delete p;
	}

	delete[] lppIPAddr;

	return TRUE;
}

BOOL sockaddr_IN_2_A(const HP_SOCKADDR& addr, ADDRESS_FAMILY& usFamily, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)
{
	BOOL isOK	= FALSE;

	usFamily	= addr.family;
	usPort		= addr.Port();

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
	if(::InetNtop(addr.family, addr.SinAddr(), lpszAddress, iAddressLen))
	{
		iAddressLen	= lstrlen(lpszAddress) + 1;
		isOK		= TRUE;
	}
	else
	{
		if(::WSAGetLastError() == ERROR_INVALID_PARAMETER)
			iAddressLen = HP_SOCKADDR::AddrMinStrLength(usFamily);
	}
#else
	if(::WSAAddressToString((LPSOCKADDR)addr.Addr(), addr.AddrSize(), nullptr, lpszAddress, (LPDWORD)&iAddressLen) == NO_ERROR)
	{
		LPTSTR lpszEnd	= nullptr;
		BOOL bIPv6		= addr.IsIPv6();
		BOOL bHasPort	= (addr.Port() != 0);

		if(!bIPv6)
		{
			if(bHasPort)
				lpszEnd = ::StrChr(lpszAddress, PORT_SEPARATOR_CHAR);
		}
		else
		{
			if(bHasPort)
			{
				static const TCHAR s_szBrk[] = {IPV6_ADDR_END_CHAR, IPV6_ZONE_INDEX_CHAR, 0};

				ASSERT(lpszAddress[0] == IPV6_ADDR_BEGIN_CHAR);
				lpszEnd = ::StrPBrk(lpszAddress, s_szBrk);
			}
			else
			{
				lpszEnd = ::StrChr(lpszAddress, IPV6_ZONE_INDEX_CHAR);
			}
		}

		ASSERT(!bHasPort || lpszEnd);

		if(lpszEnd)
		{
			lpszEnd[0]	= 0;
			iAddressLen	= lpszEnd - lpszAddress;
		}

		if(bIPv6 && bHasPort)
			memcpy(lpszAddress, (lpszAddress + 1), iAddressLen * sizeof(TCHAR));
		else
			++iAddressLen;

		isOK = TRUE;
	}
#endif

	return isOK;
}

BOOL sockaddr_A_2_IN(LPCTSTR lpszAddress, USHORT usPort, HP_SOCKADDR& addr)
{
	addr.family = DetermineAddrFamily(lpszAddress);
	return GetSockAddr(lpszAddress, usPort, addr);
}

BOOL GetSocketAddress(SOCKET socket, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort, BOOL bLocal)
{
	HP_SOCKADDR addr;

	int addr_len = addr.AddrSize();
	int result	 = bLocal ? getsockname(socket, addr.Addr(), &addr_len) : getpeername(socket, addr.Addr(), &addr_len);

	if(result != NO_ERROR)
		return FALSE;

	ADDRESS_FAMILY usFamily;
	return sockaddr_IN_2_A(addr, usFamily, lpszAddress, iAddressLen, usPort);
}

BOOL GetSocketLocalAddress(SOCKET socket, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)
{
	return GetSocketAddress(socket, lpszAddress, iAddressLen, usPort, TRUE);
}

BOOL GetSocketRemoteAddress(SOCKET socket, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)
{
	return GetSocketAddress(socket, lpszAddress, iAddressLen, usPort, FALSE);
}

ULONGLONG NToH64(ULONGLONG value)
{
	return (((ULONGLONG)ntohl((u_long)((value << 32) >> 32))) << 32) | ntohl((u_long)(value >> 32));
}

ULONGLONG HToN64(ULONGLONG value)
{
	return (((ULONGLONG)htonl((u_long)((value << 32) >> 32))) << 32) | htonl((u_long)(value >> 32));
}

BOOL IsLittleEndian()
{
	static const USHORT _s_endian_test_value = 0x0102;
	static const BOOL _s_bLE = (*((BYTE*)&_s_endian_test_value) == 0x02);

	return _s_bLE;
}

USHORT HToLE16(USHORT value)
{
	return IsLittleEndian() ? value : ENDIAN_SWAP_16(value);
}

USHORT HToBE16(USHORT value)
{
	return IsLittleEndian() ? ENDIAN_SWAP_16(value) : value;
}

DWORD HToLE32(DWORD value)
{
	return IsLittleEndian() ? value : ENDIAN_SWAP_32(value);
}

DWORD HToBE32(DWORD value)
{
	return IsLittleEndian() ? ENDIAN_SWAP_32(value) : value;
}

PVOID GetExtensionFuncPtr(SOCKET sock, GUID guid)
{
	DWORD dwBytes;
	PVOID pfn = nullptr;

	::WSAIoctl	(
					sock,
					SIO_GET_EXTENSION_FUNCTION_POINTER,
					&guid,
					sizeof(guid),
					&pfn,
					sizeof(pfn),
					&dwBytes,
					nullptr,
					nullptr
				);

	return pfn;
}

LPFN_ACCEPTEX Get_AcceptEx_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_ACCEPTEX;
	return (LPFN_ACCEPTEX)GetExtensionFuncPtr(sock, guid);
}

LPFN_GETACCEPTEXSOCKADDRS Get_GetAcceptExSockaddrs_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_GETACCEPTEXSOCKADDRS;
	return (LPFN_GETACCEPTEXSOCKADDRS)GetExtensionFuncPtr(sock, guid);
}

LPFN_CONNECTEX Get_ConnectEx_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_CONNECTEX;
	return (LPFN_CONNECTEX)GetExtensionFuncPtr(sock, guid);
}

LPFN_TRANSMITFILE Get_TransmitFile_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_TRANSMITFILE;
	return (LPFN_TRANSMITFILE)GetExtensionFuncPtr(sock, guid);
}

LPFN_DISCONNECTEX Get_DisconnectEx_FuncPtr	(SOCKET sock)
{
	GUID guid = WSAID_DISCONNECTEX;
	return (LPFN_DISCONNECTEX)GetExtensionFuncPtr(sock, guid);
}

HRESULT ReadSmallFile(LPCTSTR lpszFileName, CAtlFile& file, CAtlFileMapping<>& fmap, DWORD dwMaxFileSize)
{
	ASSERT(lpszFileName != nullptr);

	HRESULT hr = file.Create(lpszFileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);

	if(SUCCEEDED(hr))
	{
		ULONGLONG ullLen;
		hr = file.GetSize(ullLen);

		if(SUCCEEDED(hr))
		{
			if(ullLen > 0 && ullLen <= dwMaxFileSize)
				hr = fmap.MapFile(file);
			else if(ullLen == 0)
				hr = HRESULT_FROM_WIN32(ERROR_FILE_INVALID);
			else
				hr = HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
		}
	}

	return hr;
}

HRESULT MakeSmallFilePackage(LPCTSTR lpszFileName, CAtlFile& file, CAtlFileMapping<>& fmap, WSABUF szBuf[3], const LPWSABUF pHead, const LPWSABUF pTail)
{
	DWORD dwMaxFileSize = MAX_SMALL_FILE_SIZE - (pHead ? pHead->len : 0) - (pTail ? pTail->len : 0);
	ASSERT(dwMaxFileSize <= MAX_SMALL_FILE_SIZE);

	HRESULT hr = ReadSmallFile(lpszFileName, file, fmap, dwMaxFileSize);

	if(SUCCEEDED(hr))
	{
		szBuf[1].len = (ULONG)fmap.GetMappingSize();
		szBuf[1].buf = fmap;

		if(pHead) memcpy(&szBuf[0], pHead, sizeof(WSABUF));
		else	  memset(&szBuf[0], 0, sizeof(WSABUF));

		if(pTail) memcpy(&szBuf[2], pTail, sizeof(WSABUF));
		else	  memset(&szBuf[2], 0, sizeof(WSABUF));
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL PostIocpCommand(HANDLE hIOCP, EnIocpCommand enCmd, ULONG_PTR ulParam)
{
	return ::PostQueuedCompletionStatus(hIOCP, enCmd, ulParam, nullptr);
}

BOOL PostIocpExit(HANDLE hIOCP)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_EXIT, 0);
}

BOOL PostIocpAccept(HANDLE hIOCP)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_ACCEPT, 0);
}

BOOL PostIocpDisconnect(HANDLE hIOCP, CONNID dwConnID)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_DISCONNECT, dwConnID);
}

BOOL PostIocpSend(HANDLE hIOCP, CONNID dwConnID)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_SEND, dwConnID);
}

BOOL PostIocpUnpause(HANDLE hIOCP, CONNID dwConnID)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_UNPAUSE, dwConnID);
}

BOOL PostIocpTimeout(HANDLE hIOCP, CONNID dwConnID)
{
	return PostIocpCommand(hIOCP, IOCP_CMD_TIMEOUT, dwConnID);
}

BOOL PostIocpClose(HANDLE hIOCP, CONNID dwConnID, int iErrorCode)
{
	return PostIocpCommand(hIOCP, (EnIocpCommand)iErrorCode, dwConnID);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int SSO_SetSocketOption(SOCKET sock, int level, int name, LPVOID val, int len)
{
	return setsockopt(sock, level, name, (CHAR*)val, len);
}

int SSO_GetSocketOption(SOCKET sock, int level, int name, LPVOID val, int* len)
{
	return getsockopt(sock, level, name, (CHAR*)val, len);
}

int SSO_IoctlSocket(SOCKET sock, long cmd, u_long* arg)
{
	return ioctlsocket(sock, cmd, arg);
}

int SSO_WSAIoctl(SOCKET sock, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned)
{
	return ::WSAIoctl(sock, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer, lpcbBytesReturned, nullptr, nullptr);
}

int SSO_UpdateAcceptContext(SOCKET soClient, SOCKET soBind)
{
	return setsockopt(soClient, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (CHAR*)&soBind, sizeof(SOCKET));
}

int SSO_UpdateConnectContext(SOCKET soClient, int iOption)
{
	return setsockopt(soClient, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, (CHAR*)&iOption, sizeof(int));
}

int SSO_NoBlock(SOCKET sock, BOOL bNoBlock)
{
	return ioctlsocket(sock, FIONBIO, (ULONG*)&bNoBlock);
}

int SSO_NoDelay(SOCKET sock, BOOL bNoDelay)
{
	return setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (CHAR*)&bNoDelay, sizeof(BOOL));
}

int SSO_DualStack(SOCKET sock, BOOL bDualStack)
{
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
	BOOL bVal = !bDualStack;
	return setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (CHAR*)&bVal, sizeof(BOOL));
#else
	return NO_ERROR;
#endif
}

int SSO_DontLinger(SOCKET sock, BOOL bDont)
{
	return setsockopt(sock, SOL_SOCKET, SO_DONTLINGER, (CHAR*)&bDont, sizeof(BOOL));
}

int SSO_Linger(SOCKET sock, USHORT l_onoff, USHORT l_linger)
{
	linger ln = {l_onoff, l_linger};
	return setsockopt(sock, SOL_SOCKET, SO_LINGER, (CHAR*)&ln, sizeof(linger));
}

int SSO_KeepAlive(SOCKET sock, BOOL bKeepAlive)
{
	return setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (CHAR*)&bKeepAlive, sizeof(BOOL));
}

int SSO_KeepAliveVals(SOCKET sock, u_long onoff, u_long time, u_long interval)
{
	int result		 = NO_ERROR;
	tcp_keepalive in = {onoff, time, interval};
	DWORD dwBytes;

	if(::WSAIoctl	(
						sock, 
						SIO_KEEPALIVE_VALS, 
						(LPVOID)&in, 
						sizeof(in), 
						nullptr, 
						0, 
						&dwBytes, 
						nullptr, 
						nullptr
					) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();
		if(result == WSAEWOULDBLOCK)
			result = NO_ERROR;
	}

	return result;
}

int SSO_RecvBuffSize(SOCKET sock, int size)
{
	return setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (CHAR*)&size, sizeof(int));
}

int SSO_SendBuffSize(SOCKET sock, int size)
{
	return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (CHAR*)&size, sizeof(int));
}

int SSO_RecvTimeOut(SOCKET sock, int ms)
{
	return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (CHAR*)&ms, sizeof(int));
}

int SSO_SendTimeOut(SOCKET sock, int ms)
{
	return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (CHAR*)&ms, sizeof(int));
}

int SSO_ReuseAddress(SOCKET sock, EnReuseAddressPolicy opt)
{
	BOOL bSet	= TRUE;
	BOOL bUnSet	= FALSE;
	int rs		= NO_ERROR;

	if(opt == RAP_NONE)
	{
		rs  = setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (CHAR*)&bSet, sizeof(BOOL));
		rs |= setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (CHAR*)&bUnSet, sizeof(BOOL));
	}
	else if(opt == RAP_ADDR_ONLY)
	{
		rs  = setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (CHAR*)&bUnSet, sizeof(BOOL));
		rs |= setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (CHAR*)&bUnSet, sizeof(BOOL));
	}
	else if(opt == RAP_ADDR_AND_PORT)
	{
		rs  = setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (CHAR*)&bUnSet, sizeof(BOOL));
		rs |= setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (CHAR*)&bSet, sizeof(BOOL));
	}
	else
	{
		::SetLastError(ERROR_INVALID_PARAMETER);
		rs = SOCKET_ERROR;
	}

	return rs;
}

int SSO_ExclusiveAddressUse(SOCKET sock, BOOL bExclusive)
{
	return setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (CHAR*)&bExclusive, sizeof(BOOL));
}

int SSO_UDP_ConnReset(SOCKET sock, BOOL bNewBehavior)
{
	int result = NO_ERROR;
	DWORD dwBytes;

	if(::WSAIoctl	(
						sock, 
						SIO_UDP_CONNRESET, 
						(LPVOID)&bNewBehavior, 
						sizeof(bNewBehavior), 
						nullptr, 
						0, 
						&dwBytes, 
						nullptr, 
						nullptr
					) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();
		if(result == WSAEWOULDBLOCK)
			result = NO_ERROR;
	}

	return result;
}

int SSO_GetError(SOCKET sock)
{
	int e;
	socklen_t len = sizeof(e);

	if(IS_NO_ERROR(SSO_GetSocketOption(sock, SOL_SOCKET, SO_ERROR, &e, &len)))
		return e;

	return SOCKET_ERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

CONNID GenerateConnectionID()
{
	static volatile CONNID s_dwConnID = 0;

	CONNID dwConnID	= ::InterlockedIncrement(&s_dwConnID);
	
	if(dwConnID == 0)
		dwConnID = ::InterlockedIncrement(&s_dwConnID);

	return dwConnID;
}

int IsUdpCloseNotify(const BYTE* pData, int iLength)
{
	return (iLength == s_iUdpCloseNotifySize								&&
			memcmp(pData, s_szUdpCloseNotify, s_iUdpCloseNotifySize) == 0)	;
}

int SendUdpCloseNotify(SOCKET sock)
{
	return send(sock, (LPCSTR)s_szUdpCloseNotify, s_iUdpCloseNotifySize, 0);
}

int SendUdpCloseNotify(SOCKET sock, const HP_SOCKADDR& remoteAddr)
{
	return sendto(sock, (LPCSTR)s_szUdpCloseNotify, s_iUdpCloseNotifySize, 0, remoteAddr.Addr(), remoteAddr.AddrSize());
}

int ManualCloseSocket(SOCKET sock, int iShutdownFlag, BOOL bGraceful)
{
	if(!bGraceful)
		SSO_Linger(sock, 1, 0);

	if(iShutdownFlag != 0xFF)
		shutdown(sock, iShutdownFlag);

	return closesocket(sock);
}

int PostAccept(LPFN_ACCEPTEX pfnAcceptEx, SOCKET soListen, SOCKET soClient, TBufferObj* pBufferObj, ADDRESS_FAMILY usFamily)
{
	int result = PostAcceptNotCheck(pfnAcceptEx, soListen, soClient, pBufferObj, usFamily);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostAcceptNotCheck(LPFN_ACCEPTEX pfnAcceptEx, SOCKET soListen, SOCKET soClient, TBufferObj* pBufferObj, ADDRESS_FAMILY usFamily)
{
	int result				= NO_ERROR;
	pBufferObj->client		= soClient;
	pBufferObj->operation	= SO_ACCEPT;
	int iAddrLen			= HP_SOCKADDR::AddrSize(usFamily) + 16;

	if(!pfnAcceptEx	(
						soListen,
						pBufferObj->client,
						pBufferObj->buff.buf,
						0,
						iAddrLen,
						iAddrLen,
						nullptr,
						&pBufferObj->ov
					)
	)
	{
		result = ::WSAGetLastError();
	}

	return result;
}

int PostConnect(LPFN_CONNECTEX pfnConnectEx, SOCKET soClient, const HP_SOCKADDR& sockAddr, TBufferObj* pBufferObj)
{
	int result = PostConnectNotCheck(pfnConnectEx, soClient, sockAddr, pBufferObj);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostConnectNotCheck(LPFN_CONNECTEX pfnConnectEx, SOCKET soClient, const HP_SOCKADDR& sockAddr, TBufferObj* pBufferObj)
{
	int result				= NO_ERROR;
	pBufferObj->client		= soClient;
	pBufferObj->operation	= SO_CONNECT;

	if(!pfnConnectEx	(
							soClient,
							sockAddr.Addr(),
							sockAddr.AddrSize(),
							nullptr,
							0,
							nullptr,
							&pBufferObj->ov
						)
	)
	{
		result = ::WSAGetLastError();
	}

	return result;
}

int PostSend(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	int result = PostSendNotCheck(pSocketObj, pBufferObj);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostSendNotCheck(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	int result				= NO_ERROR;
	DWORD dwBytes			= 0;
	pBufferObj->client		= pSocketObj->socket;
	pBufferObj->operation	= SO_SEND;

	pBufferObj->ResetSendCounter();
	pSocketObj->Increment();

	if(::WSASend(
					pBufferObj->client,
					&pBufferObj->buff,
					1,
					&dwBytes,
					0,
					&pBufferObj->ov,
					nullptr
				) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();

		if(result != WSA_IO_PENDING)
			pSocketObj->Decrement();
	}

	return result;
}

int PostReceive(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	int result = PostReceiveNotCheck(pSocketObj, pBufferObj);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostReceiveNotCheck(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	int result				= NO_ERROR;
	DWORD dwFlag			= 0;
	DWORD dwBytes			= 0;
	pBufferObj->client		= pSocketObj->socket;
	pBufferObj->operation	= SO_RECEIVE;

	pSocketObj->Increment();

	if(::WSARecv(
					pBufferObj->client,
					&pBufferObj->buff,
					1,
					&dwBytes,
					&dwFlag,
					&pBufferObj->ov,
					nullptr
				) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();

		if(result != WSA_IO_PENDING)
			pSocketObj->Decrement();
	}

	return result;
}

int PostSendTo(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result = PostSendToNotCheck(sock, pBufferObj);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostSendToNotCheck(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result				= NO_ERROR;
	DWORD dwBytes			= 0;
	pBufferObj->operation	= SO_SEND;
	pBufferObj->addrLen		= pBufferObj->remoteAddr.AddrSize();

	pBufferObj->ResetSendCounter();

	if(::WSASendTo	(
						sock,
						&pBufferObj->buff,
						1,
						&dwBytes,
						0,
						pBufferObj->remoteAddr.Addr(),
						pBufferObj->addrLen,
						&pBufferObj->ov,
						nullptr
					) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();
	}

	return result;
}

int PostReceiveFrom(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result = PostReceiveFromNotCheck(sock, pBufferObj);

	if(result == WSA_IO_PENDING)
		result = NO_ERROR;

	return result;
}

int PostReceiveFromNotCheck(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result				= NO_ERROR;
	pBufferObj->operation	= SO_RECEIVE;
	pBufferObj->addrLen		= pBufferObj->remoteAddr.AddrSize();

	do 
	{
		DWORD dwFlag	= 0;
		DWORD dwBytes	= 0;

		if(::WSARecvFrom(
							sock,
							&pBufferObj->buff,
							1,
							&dwBytes,
							&dwFlag,
							pBufferObj->remoteAddr.Addr(),
							&pBufferObj->addrLen,
							&pBufferObj->ov,
							nullptr
						) == SOCKET_ERROR)
		{
			result = ::WSAGetLastError();
		}

		if(!IS_UDP_RESET_ERROR(result))
			break;

		pBufferObj->ResetOV();

	} while(TRUE);

	return result;
}

int NoBlockReceive(TBufferObj* pBufferObj)
{
	int result = NoBlockReceiveNotCheck(pBufferObj);

	if(result == WSAEWOULDBLOCK)
		result = NO_ERROR;

	return result;
}

int NoBlockReceiveNotCheck(TBufferObj* pBufferObj)
{
	int result		= NO_ERROR;
	DWORD dwFlag	= 0;
	DWORD dwBytes	= 0;

	if(::WSARecv(
					pBufferObj->client,
					&pBufferObj->buff,
					1,
					&dwBytes,
					&dwFlag,
					nullptr,
					nullptr
				) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();
	}
	else
	{
		if(dwBytes > 0)
			pBufferObj->buff.len = dwBytes;
		else
			result = WSAEDISCON;
	}

	return result;
}

int NoBlockReceiveFrom(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result = NoBlockReceiveFromNotCheck(sock, pBufferObj);

	if(result == WSAEWOULDBLOCK)
		result = NO_ERROR;

	return result;
}

int NoBlockReceiveFromNotCheck(SOCKET sock, TUdpBufferObj* pBufferObj)
{
	int result			= NO_ERROR;
	pBufferObj->addrLen	= pBufferObj->remoteAddr.AddrSize();

	do 
	{
		DWORD dwFlag	= 0;
		DWORD dwBytes	= 0;

		if(::WSARecvFrom(
							sock,
							&pBufferObj->buff,
							1,
							&dwBytes,
							&dwFlag,
							pBufferObj->remoteAddr.Addr(),
							&pBufferObj->addrLen,
							nullptr,
							nullptr
						) == SOCKET_ERROR)
		{
			result = ::WSAGetLastError();
		}
		else
		{
			if(dwBytes > 0)
				pBufferObj->buff.len = dwBytes;
			else
				result = WSAEDISCON;
		}

	} while(IS_UDP_RESET_ERROR(result));


	return result;
}

BOOL SetMultiCastSocketOptions(SOCKET sock, const HP_SOCKADDR& bindAddr, const HP_SOCKADDR& castAddr, int iMCTtl, BOOL bMCLoop)
{
	if(castAddr.IsIPv4())
	{
		ENSURE(::SSO_SetSocketOption(sock, IPPROTO_IP, IP_MULTICAST_TTL, &iMCTtl, sizeof(iMCTtl)) != SOCKET_ERROR);
		ENSURE(::SSO_SetSocketOption(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &bMCLoop, sizeof(bMCLoop)) != SOCKET_ERROR);

		ip_mreq mcast;
		::ZeroMemory(&mcast, sizeof(mcast));

		mcast.imr_multiaddr = castAddr.addr4.sin_addr;
		mcast.imr_interface = bindAddr.addr4.sin_addr;

		if(::SSO_SetSocketOption(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcast, sizeof(mcast)) == SOCKET_ERROR)
			return FALSE;
	}
	else
	{
		ENSURE(::SSO_SetSocketOption(sock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &iMCTtl, sizeof(iMCTtl)) != SOCKET_ERROR);
		ENSURE(::SSO_SetSocketOption(sock, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &bMCLoop, sizeof(bMCLoop)) != SOCKET_ERROR);

		ipv6_mreq mcast;
		::ZeroMemory(&mcast, sizeof(mcast));

		mcast.ipv6mr_multiaddr = castAddr.addr6.sin6_addr;
		mcast.ipv6mr_interface = bindAddr.addr6.sin6_scope_id;

		if(::SSO_SetSocketOption(sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &mcast, sizeof(mcast)) == SOCKET_ERROR)
			return FALSE;
	}

	return TRUE;
}

int WaitForSocketWrite(SOCKET sock, DWORD dwTimeout)
{
	timeval tv = {(long)(dwTimeout / 1000), (long)((dwTimeout % 1000) * 1000)};

	fd_set wfds, efds;
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	FD_SET(sock, &wfds);
	FD_SET(sock, &efds);

	int rs = select(0, nullptr, &wfds, &efds, &tv);

	if(rs <= 0) return ((rs == 0) ? ERROR_TIMEOUT : ENSURE_ERROR(ERROR_CANT_WAIT));
	
	if(FD_ISSET(sock, &efds))
	{
		rs = SSO_GetError(sock);
		return ((rs != NO_ERROR && rs != SOCKET_ERROR) ? rs : ENSURE_ERROR(ERROR_CANT_WAIT));
	}

	VERIFY(FD_ISSET(sock, &wfds));

	return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL SetCurrentWorkerThreadName()
{
	return SetWorkerThreadDefaultName(nullptr);
}

BOOL SetWorkerThreadDefaultName(HANDLE hThread)
{
	static volatile UINT _s_uiSeq = MAXUINT;

	return ::SetSequenceThreadName(hThread, DEFAULT_WORKER_THREAD_PREFIX, _s_uiSeq);
}

LPCTSTR GetSocketErrorDesc(EnSocketError enCode)
{
	switch(enCode)
	{
	case SE_OK:						return _T("SUCCESS");
	case SE_ILLEGAL_STATE:			return _T("Illegal State");
	case SE_INVALID_PARAM:			return _T("Invalid Parameter");
	case SE_SOCKET_CREATE:			return _T("Create SOCKET Fail");
	case SE_SOCKET_BIND:			return _T("Bind SOCKET Fail");
	case SE_SOCKET_PREPARE:			return _T("Prepare SOCKET Fail");
	case SE_SOCKET_LISTEN:			return _T("Listen SOCKET Fail");
	case SE_CP_CREATE:				return _T("Create IOCP Fail");
	case SE_WORKER_THREAD_CREATE:	return _T("Create Worker Thread Fail");
	case SE_DETECT_THREAD_CREATE:	return _T("Create Detector Thread Fail");
	case SE_SOCKE_ATTACH_TO_CP:		return _T("Attach SOCKET to IOCP Fail");
	case SE_CONNECT_SERVER:			return _T("Connect to Server Fail");
	case SE_NETWORK:				return _T("Network Error");
	case SE_DATA_PROC:				return _T("Process Data Error");
	case SE_DATA_SEND:				return _T("Send Data Fail");
	case SE_GC_START:				return _T("Start GC Fail");

	case SE_SSL_ENV_NOT_READY:		return _T("SSL environment not ready");

	default: ASSERT(FALSE);			return _T("UNKNOWN ERROR");
	}
}

BOOL CodePageToUnicodeEx(int iCodePage, const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength)
{
	ASSERT(szSrc);

	int iSize = ::MultiByteToWideChar(iCodePage, 0, szSrc, iSrcLength, nullptr, 0);

	if(iSize == 0 || iSize > iDestLength || !szDest || iDestLength == 0)
	{
		iDestLength = iSize;
		return FALSE;
	}

	if(::MultiByteToWideChar(iCodePage, 0, szSrc, iSrcLength, szDest, iSize) != 0)
		iDestLength = iSize;
	else
		iDestLength = 0;

	return iDestLength != 0;
}

BOOL UnicodeToCodePageEx(int iCodePage, const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength)
{
	ASSERT(szSrc);

	int iSize = ::WideCharToMultiByte(iCodePage, 0, szSrc, iSrcLength, nullptr, 0, nullptr, nullptr);

	if(iSize == 0 || iSize > iDestLength || !szDest || iDestLength == 0)
	{
		iDestLength = iSize;
		return FALSE;
	}

	if(::WideCharToMultiByte(iCodePage, 0, szSrc, iSrcLength, szDest, iSize, nullptr, nullptr) != 0)
		iDestLength = iSize;
	else
		iDestLength = 0;

	return iDestLength != 0;
}

BOOL GbkToUnicodeEx(const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength)
{
	return CodePageToUnicodeEx(CP_ACP, szSrc, iSrcLength, szDest, iDestLength);
}

BOOL UnicodeToGbkEx(const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength)
{
	return UnicodeToCodePageEx(CP_ACP, szSrc, iSrcLength, szDest, iDestLength);
}

BOOL Utf8ToUnicodeEx(const char szSrc[], int iSrcLength, WCHAR szDest[], int& iDestLength)
{
	return CodePageToUnicodeEx(CP_UTF8, szSrc, iSrcLength, szDest, iDestLength);
}

BOOL UnicodeToUtf8Ex(const WCHAR szSrc[], int iSrcLength, char szDest[], int& iDestLength)
{
	return UnicodeToCodePageEx(CP_UTF8, szSrc, iSrcLength, szDest, iDestLength);
}

BOOL GbkToUtf8Ex(const char szSrc[], int iSrcLength, char szDest[], int& iDestLength)
{
	int iMiddleLength = 0;
	GbkToUnicodeEx(szSrc, iSrcLength, nullptr, iMiddleLength);

	if(iMiddleLength == 0)
	{
		iDestLength = 0;
		return FALSE;
	}

	unique_ptr<WCHAR[]> p(new WCHAR[iMiddleLength]);
	ENSURE(GbkToUnicodeEx(szSrc, iSrcLength, p.get(), iMiddleLength));

	return UnicodeToUtf8Ex(p.get(), iMiddleLength, szDest, iDestLength);
}

BOOL Utf8ToGbkEx(const char szSrc[], int iSrcLength, char szDest[], int& iDestLength)
{
	int iMiddleLength = 0;
	Utf8ToUnicodeEx(szSrc, iSrcLength, nullptr, iMiddleLength);

	if(iMiddleLength == 0)
	{
		iDestLength = 0;
		return FALSE;
	}

	unique_ptr<WCHAR[]> p(new WCHAR[iMiddleLength]);
	ENSURE(Utf8ToUnicodeEx(szSrc, iSrcLength, p.get(), iMiddleLength));

	return UnicodeToGbkEx(p.get(), iMiddleLength, szDest, iDestLength);
}

BOOL CodePageToUnicode(int iCodePage, const char szSrc[], WCHAR szDest[], int& iDestLength)
{
	return CodePageToUnicodeEx(iCodePage, szSrc, -1, szDest, iDestLength);
}

BOOL UnicodeToCodePage(int iCodePage, const WCHAR szSrc[], char szDest[], int& iDestLength)
{
	return UnicodeToCodePageEx(iCodePage, szSrc, -1, szDest, iDestLength);
}

BOOL GbkToUnicode(const char szSrc[], WCHAR szDest[], int& iDestLength)
{
	return GbkToUnicodeEx(szSrc, -1, szDest, iDestLength);
}

BOOL UnicodeToGbk(const WCHAR szSrc[], char szDest[], int& iDestLength)
{
	return UnicodeToGbkEx(szSrc, -1, szDest, iDestLength);
}

BOOL Utf8ToUnicode(const char szSrc[], WCHAR szDest[], int& iDestLength)
{
	return Utf8ToUnicodeEx(szSrc, -1, szDest, iDestLength);
}

BOOL UnicodeToUtf8(const WCHAR szSrc[], char szDest[], int& iDestLength)
{
	return UnicodeToUtf8Ex(szSrc, -1, szDest, iDestLength);
}

BOOL GbkToUtf8(const char szSrc[], char szDest[], int& iDestLength)
{
	return GbkToUtf8Ex(szSrc, -1, szDest, iDestLength);
}

BOOL Utf8ToGbk(const char szSrc[], char szDest[], int& iDestLength)
{
	return Utf8ToGbkEx(szSrc, -1, szDest, iDestLength);
}

DWORD GuessBase64EncodeBound(DWORD dwSrcLen)
{
	return 4 * ((dwSrcLen + 2) / 3);
}

DWORD GuessBase64DecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen)
{
	if(dwSrcLen < 2)
		return 0;

	if(lpszSrc[dwSrcLen - 2] == '=')
		dwSrcLen -= 2;
	else if(lpszSrc[dwSrcLen - 1] == '=')
			--dwSrcLen;

	DWORD dwMod = dwSrcLen % 4;
	DWORD dwAdd = dwMod == 2 ? 1 : (dwMod == 3 ? 2 : 0);

	return 3 * (dwSrcLen / 4) + dwAdd;
}

int Base64Encode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	static const BYTE CODES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	DWORD dwRealLen = GuessBase64EncodeBound(dwSrcLen);

	if(lpszDest == nullptr || dwDestLen < dwRealLen)
	{
		dwDestLen = dwRealLen;
		return -5;
	}

	BYTE* p		= lpszDest;
	DWORD leven	= 3 * (dwSrcLen / 3);
	DWORD i		= 0;

	for (; i < leven; i += 3)
	{
		*p++ = CODES[lpszSrc[0] >> 2];
		*p++ = CODES[((lpszSrc[0] & 3) << 4) + (lpszSrc[1] >> 4)];
		*p++ = CODES[((lpszSrc[1] & 0xf) << 2) + (lpszSrc[2] >> 6)];
		*p++ = CODES[lpszSrc[2] & 0x3f];

		lpszSrc += 3;
	}

	if(i < dwSrcLen)
	{
		BYTE a = lpszSrc[0];
		BYTE b = (i + 1 < dwSrcLen) ? lpszSrc[1] : 0;

		*p++ = CODES[a >> 2];
		*p++ = CODES[((a & 3) << 4) + (b >> 4)];
		*p++ = (i + 1 < dwSrcLen) ? CODES[((b & 0xf) << 2)] : '=';
		*p++ = '=';
	}  

	ASSERT(dwRealLen == (DWORD)(p - lpszDest));

	if(dwDestLen > dwRealLen)
	{
		*p			= 0;
		dwDestLen	= dwRealLen;
	}

	return 0;  
}

int Base64Decode(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	static const BYTE MAP[256]	=
	{ 
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,
		255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
		 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
		255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
		  7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
		 19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
		255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
		 37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
		 49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255
	};

	DWORD dwRealLen = GuessBase64DecodeBound(lpszSrc, dwSrcLen);

	if(lpszDest == nullptr || dwDestLen < dwRealLen)
	{
		dwDestLen = dwRealLen;
		return -5;
	}

	BYTE c;
	int g = 3;
	DWORD i, x, y, z;

	for(i = x = y = z = 0; i < dwSrcLen || x != 0;)
	{
		c = i < dwSrcLen ? MAP[lpszSrc[i++]] : 254;

		if(c == 255) {dwDestLen = 0; return -3;}
		else if(c == 254) {c = 0; g--;}
		else if(c == 253) continue;

		z = (z << 6) | c;

		if(++x == 4)
		{
			lpszDest[y++] = (BYTE)((z >> 16) & 255);
			if (g > 1) lpszDest[y++] = (BYTE)((z >> 8) & 255);
			if (g > 2) lpszDest[y++] = (BYTE)(z & 255);

			x = z = 0;
		}
	}

	BOOL isOK = (y == dwRealLen);

	if(!isOK)
		dwDestLen = 0;
	else
	{
		if(dwDestLen > dwRealLen)
		{
			lpszDest[dwRealLen]	= 0;
			dwDestLen			= dwRealLen;
		}
	}

	return isOK ? 0 : -3;
}

DWORD GuessUrlEncodeBound(const BYTE* lpszSrc, DWORD dwSrcLen)
{
	DWORD dwAdd = 0;

	for(DWORD i = 0; i < dwSrcLen; i++)
	{
		BYTE c	= lpszSrc[i];

		if(!(isalnum(c) || c == ' ' || c == '.' || c == '-' || c == '_' || c == '*'))
			dwAdd += 2;
	}

	return dwSrcLen + dwAdd;
}

DWORD GuessUrlDecodeBound(const BYTE* lpszSrc, DWORD dwSrcLen)
{
	DWORD dwPercent = 0;

	for(DWORD i = 0; i < dwSrcLen; i++)
	{
		if(lpszSrc[i] == '%')
		{
			++dwPercent;
			i += 2;
		}
	}

	DWORD dwSub = dwPercent * 2;

	if(dwSrcLen < dwSub)
		return 0;

	return dwSrcLen - dwSub;
}

int UrlEncode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	BYTE c;
	DWORD j = 0;

	if(lpszDest == nullptr || dwDestLen == 0)
		goto ERROR_DEST_LEN;

	for(DWORD i = 0; i < dwSrcLen; i++)
	{
		if(j >= dwDestLen)
			goto ERROR_DEST_LEN;

		c = lpszSrc[i];

		if (isalnum(c) || c == '.' || c == '-' || c == '_' || c == '*')
			lpszDest[j++] = c;
		else if(c == ' ')
			lpszDest[j++] = '+';
		else
		{
			if(j + 3 >= dwDestLen)
				goto ERROR_DEST_LEN;

			lpszDest[j++] = '%';
			HEX_VALUE_TO_DOUBLE_CHAR(lpszDest + j, c);
			j += 2;
			
		}
	}

	if(dwDestLen > j)
	{
		lpszDest[j]	= 0;
		dwDestLen	= j;
	}

	return 0;

ERROR_DEST_LEN:
	dwDestLen = GuessUrlEncodeBound(lpszSrc, dwSrcLen);
	return -5;
}

int UrlDecode(BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	char c;
	DWORD j = 0;

	if(lpszDest == nullptr || dwDestLen == 0)
		goto ERROR_DEST_LEN;

	for(DWORD i = 0; i < dwSrcLen; i++)
	{
		if(j >= dwDestLen)
			goto ERROR_DEST_LEN;

		c = lpszSrc[i];

		if(c == '+')
			lpszDest[j++] = ' ';
		else if(c != '%')
			lpszDest[j++] = c;
		else
		{
			if(i + 2 >= dwSrcLen)
				goto ERROR_SRC_DATA;

			lpszDest[j++] = HEX_DOUBLE_CHAR_TO_VALUE(lpszSrc + i + 1);
			i += 2;
		}
	}

	if(dwDestLen > j)
	{
		lpszDest[j]	= 0;
		dwDestLen	= j;
	}

	return 0;

ERROR_SRC_DATA:
	dwDestLen = 0;
	return -3;

ERROR_DEST_LEN:
	dwDestLen = GuessUrlDecodeBound(lpszSrc, dwSrcLen);
	return -5;
}

void DestroyCompressor(IHPCompressor* pCompressor)
{
	delete pCompressor;
}

void DestroyDecompressor(IHPDecompressor* pDecompressor)
{
	delete pDecompressor;
}

#ifdef _ZLIB_SUPPORT

CHPZLibCompressor::CHPZLibCompressor(Fn_CompressDataCallback fnCallback, int iWindowBits, int iLevel, int iMethod, int iMemLevel, int iStrategy, DWORD dwBuffSize)
: m_fnCallback	(fnCallback)
, m_dwBuffSize	(dwBuffSize)
, m_bValid		(FALSE)
{
	ASSERT(m_fnCallback != nullptr);

	::ZeroObject(m_Stream);

	m_bValid = (::deflateInit2(&m_Stream, iLevel, iMethod, iWindowBits, iMemLevel, iStrategy) == Z_OK);
}
CHPZLibCompressor::~CHPZLibCompressor()
{
	if(m_bValid) ::deflateEnd(&m_Stream);
}

BOOL CHPZLibCompressor::Reset()
{
	return (m_bValid = (::deflateReset(&m_Stream) == Z_OK));
}

BOOL CHPZLibCompressor::Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext)
{
	return ProcessEx(pData, iLength, bLast, FALSE, pContext);
}

BOOL CHPZLibCompressor::ProcessEx(const BYTE* pData, int iLength, BOOL bLast, BOOL bFlush, PVOID pContext)
{
	ASSERT(IsValid() && iLength > 0);

	if(!IsValid())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	unique_ptr<BYTE[]> szBuff(new BYTE[m_dwBuffSize]);

	m_Stream.next_in	= (z_const Bytef*)pData;
	m_Stream.avail_in	= iLength;
	
	BOOL isOK	= TRUE;
	int rs		= Z_OK;
	int flush	= bLast ? Z_FINISH : (bFlush ? Z_SYNC_FLUSH : Z_NO_FLUSH);

	while(m_Stream.avail_in > 0)
	{
		do
		{
			m_Stream.next_out  = szBuff.get();
			m_Stream.avail_out = m_dwBuffSize;

			rs = ::deflate(&m_Stream, flush);

			if(rs == Z_STREAM_ERROR)
			{
				::SetLastError(ERROR_INVALID_DATA);
				isOK = FALSE;
				
				goto ZLIB_COMPRESS_END;
			}

			int iRead = (int)(m_dwBuffSize - m_Stream.avail_out);

			if(iRead == 0)
				break;

			if(!m_fnCallback(szBuff.get(), iRead, pContext))
			{
				::SetLastError(ERROR_CANCELLED);
				isOK = FALSE;

				goto ZLIB_COMPRESS_END;
			}
		} while(m_Stream.avail_out == 0);
	}

ZLIB_COMPRESS_END:

	ASSERT(!isOK || (rs == Z_OK && !bLast) || (rs == Z_STREAM_END && bLast));

	if(!isOK || bLast) Reset();

	return isOK;
}

CHPZLibDecompressor::CHPZLibDecompressor(Fn_DecompressDataCallback fnCallback, int iWindowBits, DWORD dwBuffSize)
: m_fnCallback	(fnCallback)
, m_dwBuffSize	(dwBuffSize)
, m_bValid		(FALSE)
{
	ASSERT(m_fnCallback != nullptr);

	::ZeroObject(m_Stream);

	m_bValid = (::inflateInit2(&m_Stream, iWindowBits) == Z_OK);
}
CHPZLibDecompressor::~CHPZLibDecompressor()
{
	if(m_bValid) ::inflateEnd(&m_Stream);
}

BOOL CHPZLibDecompressor::Reset()
{
	return (m_bValid = (::inflateReset(&m_Stream) == Z_OK));
}

BOOL CHPZLibDecompressor::Process(const BYTE* pData, int iLength, PVOID pContext)
{
	ASSERT(IsValid() && iLength > 0);

	if(!IsValid())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	unique_ptr<BYTE[]> szBuff(new BYTE[m_dwBuffSize]);

	m_Stream.next_in	= (z_const Bytef*)pData;
	m_Stream.avail_in	= iLength;

	BOOL isOK	= TRUE;
	int rs		= Z_OK;

	while(m_Stream.avail_in > 0)
	{
		do
		{
			m_Stream.next_out  = szBuff.get();
			m_Stream.avail_out = m_dwBuffSize;

			rs = ::inflate(&m_Stream, Z_NO_FLUSH);

			if(rs != Z_OK && rs != Z_STREAM_END)
			{
				::SetLastError(ERROR_INVALID_DATA);
				isOK = FALSE;

				goto ZLIB_DECOMPRESS_END;
			}

			int iRead = (int)(m_dwBuffSize - m_Stream.avail_out);

			if(iRead == 0)
				break;

			if(!m_fnCallback(szBuff.get(), iRead, pContext))
			{
				::SetLastError(ERROR_CANCELLED);
				isOK = FALSE;

				goto ZLIB_DECOMPRESS_END;
			}
		} while(m_Stream.avail_out == 0);

		if(rs == Z_STREAM_END)
			break;
	}

ZLIB_DECOMPRESS_END:

	ASSERT(!isOK || rs == Z_OK || rs == Z_STREAM_END);

	if(!isOK || rs == Z_STREAM_END) Reset();

	return isOK;
}

IHPCompressor* CreateZLibCompressor(Fn_CompressDataCallback fnCallback, int iWindowBits, int iLevel, int iMethod, int iMemLevel, int iStrategy, DWORD dwBuffSize)
{
	return new CHPZLibCompressor(fnCallback, iWindowBits, iLevel, iMethod, iMemLevel, iStrategy, dwBuffSize);
}

IHPCompressor* CreateGZipCompressor(Fn_CompressDataCallback fnCallback, int iLevel, int iMethod, int iMemLevel, int iStrategy, DWORD dwBuffSize)
{
	return new CHPZLibCompressor(fnCallback, MAX_WBITS + 16, iLevel, iMethod, iMemLevel, iStrategy, dwBuffSize);
}

IHPDecompressor* CreateZLibDecompressor(Fn_DecompressDataCallback fnCallback, int iWindowBits, DWORD dwBuffSize)
{
	return new CHPZLibDecompressor(fnCallback, iWindowBits, dwBuffSize);
}

IHPDecompressor* CreateGZipDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize)
{
	return new CHPZLibDecompressor(fnCallback, MAX_WBITS + 32, dwBuffSize);
}

int Compress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	return CompressEx(lpszSrc, dwSrcLen, lpszDest, dwDestLen);
}

int CompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iLevel, int iMethod, int iWindowBits, int iMemLevel, int iStrategy)
{
	z_stream stream;

	stream.next_in	 = (z_const Bytef*)lpszSrc;
	stream.avail_in	 = dwSrcLen;
	stream.next_out	 = lpszDest;
	stream.avail_out = dwDestLen;
	stream.zalloc	 = nullptr;
	stream.zfree	 = nullptr;
	stream.opaque	 = nullptr;

	int err = ::deflateInit2(&stream, iLevel, iMethod, iWindowBits, iMemLevel, iStrategy);

	if(err != Z_OK) return err;

	err = ::deflate(&stream, Z_FINISH);

	if(err != Z_STREAM_END)
	{
		::deflateEnd(&stream);
		return err == Z_OK ? Z_BUF_ERROR : err;
	}

	if(dwDestLen > stream.total_out)
	{
		lpszDest[stream.total_out]	= 0;
		dwDestLen					= stream.total_out;
	}

	return ::deflateEnd(&stream);
}

int Uncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	return UncompressEx(lpszSrc, dwSrcLen, lpszDest, dwDestLen);
}

int UncompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iWindowBits)
{
	z_stream stream;

	stream.next_in	 = (z_const Bytef*)lpszSrc;
	stream.avail_in	 = dwSrcLen;
	stream.next_out	 = lpszDest;
	stream.avail_out = dwDestLen;
	stream.zalloc	 = nullptr;
	stream.zfree	 = nullptr;

	int err = ::inflateInit2(&stream, iWindowBits);

	if(err != Z_OK) return err;

	err = ::inflate(&stream, Z_FINISH);

	if(err != Z_STREAM_END)
	{
		::inflateEnd(&stream);
		return (err == Z_NEED_DICT || (err == Z_BUF_ERROR && stream.avail_in == 0)) ? Z_DATA_ERROR : err;
	}

	if(dwDestLen > stream.total_out)
	{
		lpszDest[stream.total_out]	= 0;
		dwDestLen					= stream.total_out;
	}

	return inflateEnd(&stream);
}

DWORD GuessCompressBound(DWORD dwSrcLen, BOOL bGZip)
{
	DWORD dwBound = ::compressBound(dwSrcLen);

	if(bGZip) dwBound += 16;

	return dwBound;
}

int GZipCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	return CompressEx(lpszSrc, dwSrcLen, lpszDest, dwDestLen, Z_DEFAULT_COMPRESSION, Z_DEFLATED, MAX_WBITS + 16);
}

int GZipUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	return UncompressEx(lpszSrc, dwSrcLen, lpszDest, dwDestLen, MAX_WBITS + 32);
}

DWORD GZipGuessUncompressBound(const BYTE* lpszSrc, DWORD dwSrcLen)
{
	if(dwSrcLen < 20 || *(USHORT*)lpszSrc != 0x8B1F)
		return 0;

	return *(DWORD*)(lpszSrc + dwSrcLen - 4);
}

#endif

#ifdef _BROTLI_SUPPORT

CHPBrotliCompressor::CHPBrotliCompressor(Fn_CompressDataCallback fnCallback, int iQuality, int iWindow, int iMode, DWORD dwBuffSize)
: m_fnCallback	(fnCallback)
, m_iQuality	(iQuality)
, m_iWindow		(iWindow)
, m_iMode		(iMode)
, m_dwBuffSize	(dwBuffSize)
, m_bValid		(FALSE)
{
	ASSERT(m_fnCallback != nullptr);

	Reset();
}

CHPBrotliCompressor::~CHPBrotliCompressor()
{
	if(m_bValid) ::BrotliEncoderDestroyInstance(m_pState);
}

BOOL CHPBrotliCompressor::Reset()
{
	if(m_bValid) ::BrotliEncoderDestroyInstance(m_pState);
	m_pState =   ::BrotliEncoderCreateInstance(nullptr, nullptr, nullptr);

	if(m_pState != nullptr)
	{
		::BrotliEncoderSetParameter(m_pState, BROTLI_PARAM_QUALITY	, (UINT)m_iQuality);
		::BrotliEncoderSetParameter(m_pState, BROTLI_PARAM_LGWIN	, (UINT)m_iWindow);
		::BrotliEncoderSetParameter(m_pState, BROTLI_PARAM_MODE		, (UINT)m_iMode);

		if (m_iWindow > BROTLI_MAX_WINDOW_BITS)
			::BrotliEncoderSetParameter(m_pState, BROTLI_PARAM_LARGE_WINDOW, BROTLI_TRUE);
	}

	return (m_bValid = (m_pState != nullptr));
}

BOOL CHPBrotliCompressor::Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext)
{
	return ProcessEx(pData, iLength, bLast, FALSE, pContext);
}

BOOL CHPBrotliCompressor::ProcessEx(const BYTE* pData, int iLength, BOOL bLast, BOOL bFlush, PVOID pContext)
{
	ASSERT(IsValid() && iLength > 0);

	if(!IsValid())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	unique_ptr<BYTE[]> szBuff(new BYTE[m_dwBuffSize]);

	const BYTE* pNextInData	= pData;
	size_t iAvlInLen		= (SIZE_T)iLength;
	BYTE* pNextOutData		= nullptr;
	size_t iAvlOutLen		= 0;

	BOOL isOK				  = TRUE;
	BrotliEncoderOperation op = bLast ? BROTLI_OPERATION_FINISH : (bFlush ? BROTLI_OPERATION_FLUSH : BROTLI_OPERATION_PROCESS);

	while(iAvlInLen > 0)
	{
		do
		{
			pNextOutData = szBuff.get();
			iAvlOutLen	 = m_dwBuffSize;

			if(!::BrotliEncoderCompressStream(m_pState, op, &iAvlInLen, &pNextInData, &iAvlOutLen, &pNextOutData, nullptr))
			{
				::SetLastError(ERROR_INVALID_DATA);
				isOK = FALSE;

				goto BROTLI_COMPRESS_END;
			}

			int iRead = (int)(m_dwBuffSize - iAvlOutLen);

			if(iRead == 0)
				break;

			if(!m_fnCallback(szBuff.get(), iRead, pContext))
			{
				::SetLastError(ERROR_CANCELLED);
				isOK = FALSE;
				
				goto BROTLI_COMPRESS_END;
			}
		} while (iAvlOutLen == 0);
	}

BROTLI_COMPRESS_END:

	if(!isOK || bLast) Reset();

	return isOK;
}

CHPBrotliDecompressor::CHPBrotliDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize)
: m_fnCallback	(fnCallback)
, m_dwBuffSize	(dwBuffSize)
, m_bValid		(FALSE)
{
	ASSERT(m_fnCallback != nullptr);

	Reset();
}

CHPBrotliDecompressor::~CHPBrotliDecompressor()
{
	if(m_bValid) ::BrotliDecoderDestroyInstance(m_pState);
}

BOOL CHPBrotliDecompressor::Reset()
{
	if(m_bValid) ::BrotliDecoderDestroyInstance(m_pState);
	m_pState =   ::BrotliDecoderCreateInstance(nullptr, nullptr, nullptr);

	return (m_bValid = (m_pState != nullptr));
}

BOOL CHPBrotliDecompressor::Process(const BYTE* pData, int iLength, PVOID pContext)
{
	ASSERT(IsValid() && iLength > 0);

	if(!IsValid())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	unique_ptr<BYTE[]> szBuff(new BYTE[m_dwBuffSize]);

	const BYTE* pNextInData	= pData;
	size_t iAvlInLen		= (SIZE_T)iLength;
	BYTE* pNextOutData		= nullptr;
	size_t iAvlOutLen		= 0;

	BOOL isOK				= TRUE;
	BrotliDecoderResult rs	= BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;

	do
	{
		do
		{
			pNextOutData = szBuff.get();
			iAvlOutLen	 = m_dwBuffSize;

			rs = ::BrotliDecoderDecompressStream(m_pState, &iAvlInLen, &pNextInData, &iAvlOutLen, &pNextOutData, nullptr);

			if(rs == BROTLI_DECODER_RESULT_ERROR)
			{
				::SetLastError(ERROR_INVALID_DATA);
				isOK = FALSE;

				goto BROTLI_DECOMPRESS_END;
			}

			int iRead = (int)(m_dwBuffSize - iAvlOutLen);

			if(iRead == 0)
				break;

			if(!m_fnCallback(szBuff.get(), iRead, pContext))
			{
				::SetLastError(ERROR_CANCELLED);
				isOK = FALSE;

				goto BROTLI_DECOMPRESS_END;
			}
		} while (iAvlOutLen == 0);

		if(rs == BROTLI_DECODER_RESULT_SUCCESS)
			break;

	} while(rs == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT);

BROTLI_DECOMPRESS_END:

	if(!isOK || rs == BROTLI_DECODER_RESULT_SUCCESS) Reset();

	return isOK;
}

IHPCompressor* CreateBrotliCompressor(Fn_CompressDataCallback fnCallback, int iQuality, int iWindow, int iMode, DWORD dwBuffSize)
{
	return new CHPBrotliCompressor(fnCallback, iQuality, iWindow, iMode, dwBuffSize);
}

IHPDecompressor* CreateBrotliDecompressor(Fn_DecompressDataCallback fnCallback, DWORD dwBuffSize)
{
	return new CHPBrotliDecompressor(fnCallback, dwBuffSize);
}

int BrotliCompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	return BrotliCompressEx(lpszSrc, dwSrcLen, lpszDest, dwDestLen, BROTLI_DEFAULT_QUALITY, BROTLI_DEFAULT_WINDOW, BROTLI_DEFAULT_MODE);
}

int BrotliCompressEx(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen, int iQuality, int iWindow, int iMode)
{
	size_t stDestLen = (size_t)dwDestLen;
	int rs = ::BrotliEncoderCompress(iQuality, iWindow, (BrotliEncoderMode)iMode, (size_t)dwSrcLen, lpszSrc, &stDestLen, lpszDest);
	dwDestLen = (DWORD)stDestLen;

	return (rs == 1) ? 0 : ((rs == 3) ? -5 : -3);
}

int BrotliUncompress(const BYTE* lpszSrc, DWORD dwSrcLen, BYTE* lpszDest, DWORD& dwDestLen)
{
	size_t stDestLen = (size_t)dwDestLen;
	BrotliDecoderResult rs = ::BrotliDecoderDecompress((size_t)dwSrcLen, lpszSrc, &stDestLen, lpszDest);
	dwDestLen = (DWORD)stDestLen;

	return (rs == BROTLI_DECODER_RESULT_SUCCESS) ? 0 : ((rs == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) ? -5 : -3);
}

DWORD BrotliGuessCompressBound(DWORD dwSrcLen)
{
	return (DWORD)::BrotliEncoderMaxCompressedSize((size_t)dwSrcLen);
}

#endif


/* ========================================================================== */
/*  MiscHelper.cpp
/*  source: Windows\Src\MiscHelper.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "MiscHelper.h" */

BOOL AddPackHeader(const WSABUF * pBuffers, int iCount, unique_ptr<WSABUF[]>& buffers, DWORD dwMaxPackSize, USHORT usPackHeaderFlag, DWORD& dwHeader)
{
	ASSERT(pBuffers && iCount > 0);

	DWORD iLength = 0;

	for(int i = 0; i < iCount; i++)
	{
		const WSABUF& buf	= pBuffers[i];
		buffers[i + 1]		= buf;
		iLength			   += buf.len;
	}

	if(iLength == 0 || iLength > dwMaxPackSize)
	{
		::SetLastError(ERROR_BAD_LENGTH);
		return FALSE;
	}

	dwHeader = ::HToLE32((usPackHeaderFlag << TCP_PACK_LENGTH_BITS) | iLength);

	buffers[0].len = sizeof(dwHeader);
	buffers[0].buf = (char*)&dwHeader;

	return TRUE;
}


/* ========================================================================== */
/*  TcpServer.cpp
/*  source: Windows\Src\TcpServer.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "TcpServer.h" */
/* [amalgamated] #include "Common/WaitFor.h" */

#include <malloc.h>
#include <process.h>

const CInitSocket CTcpServer::sm_wsSocket;

EnHandleResult CTcpServer::TriggerFireAccept(TSocketObj* pSocketObj)
{
	EnHandleResult rs = TRIGGER(FireAccept(pSocketObj));
	pSocketObj->csRecv.Unlock();

	return rs;
}

EnHandleResult CTcpServer::TriggerFireReceive(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	EnHandleResult rs = (EnHandleResult)HR_CLOSED;

	if(TSocketObj::IsValid(pSocketObj))
	{
		CCriSecLock locallock(pSocketObj->csRecv);

		if(TSocketObj::IsValid(pSocketObj))
		{
			rs = TRIGGER(FireReceive(pSocketObj, (BYTE*)pBufferObj->buff.buf, pBufferObj->buff.len));
		}
	}

	return rs;
}

EnHandleResult CTcpServer::TriggerFireSend(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	EnHandleResult rs = (EnHandleResult)HR_CLOSED;

	if(m_enOnSendSyncPolicy == OSSP_NONE)
		rs = TRIGGER(FireSend(pSocketObj, (BYTE*)pBufferObj->buff.buf, pBufferObj->buff.len));
	else
	{
		ASSERT(m_enOnSendSyncPolicy >= OSSP_CLOSE && m_enOnSendSyncPolicy <= OSSP_RECEIVE);

		if(TSocketObj::IsValid(pSocketObj))
		{
			CCriSecLock locallock(m_enOnSendSyncPolicy == OSSP_CLOSE ? pSocketObj->csSend : pSocketObj->csRecv);

			if(TSocketObj::IsValid(pSocketObj))
			{
				rs = TRIGGER(FireSend(pSocketObj, (BYTE*)pBufferObj->buff.buf, pBufferObj->buff.len));
			}
		}
	}

	if(rs == HR_ERROR)
	{
		TRACE("<S-CNNID: %Iu> OnSend() event should not return 'HR_ERROR' !!\n", pSocketObj->connID);
		ASSERT(FALSE);
	}

	return rs;
}

EnHandleResult CTcpServer::TriggerFireClose(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
{
	CCriSecLock locallock(pSocketObj->csRecv);
	return FireClose(pSocketObj, enOperation, iErrorCode);
}

void CTcpServer::SetLastError(EnSocketError code, LPCSTR func, int ec)
{
	m_enLastError = code;
	::SetLastError(ec);

	TRACE("%s --> Error: %d, EC: %d\n", func, code, ec);
}

BOOL CTcpServer::Start(LPCTSTR lpszBindAddress, USHORT usPort)
{
	if(!CheckParams() || !CheckStarting())
		return FALSE;

	PrepareStart();

	if(CreateListenSocket(lpszBindAddress, usPort))
		if(CreateCompletePort())
			if(CreateWorkerThreads())
				if(StartAccept())
				{
					m_enState = SS_STARTED;
					
					m_evWait.Reset();

					return TRUE;
				}

	EXECUTE_RESTORE_ERROR(Stop());

	return FALSE;
}

BOOL CTcpServer::CheckParams()
{
	if	((m_enSendPolicy >= SP_PACK && m_enSendPolicy <= SP_DIRECT)								&&
		(m_enOnSendSyncPolicy >= OSSP_NONE && m_enOnSendSyncPolicy <= OSSP_RECEIVE)				&&
		((int)m_dwMaxConnectionCount > 0 && m_dwMaxConnectionCount <= MAX_CONNECTION_COUNT)		&&
		((int)m_dwWorkerThreadCount > 0 && m_dwWorkerThreadCount <= MAX_WORKER_THREAD_COUNT)	&&
		((int)m_dwAcceptSocketCount > 0)														&&
		((int)m_dwSocketBufferSize >= MIN_SOCKET_BUFFER_SIZE)									&&
		((int)m_dwSocketListenQueue > 0)														&&
		((int)m_dwFreeSocketObjLockTime >= 1000)												&&
		((int)m_dwFreeSocketObjPool >= 0)														&&
		((int)m_dwFreeBufferObjPool >= 0)														&&
		((int)m_dwFreeSocketObjHold >= 0)														&&
		((int)m_dwFreeBufferObjHold >= 0)														&&
		((int)m_dwKeepAliveTime >= 1000 || m_dwKeepAliveTime == 0)								&&
		((int)m_dwKeepAliveInterval >= 1000 || m_dwKeepAliveInterval == 0)						)
		return TRUE;

	SetLastError(SE_INVALID_PARAM, __FUNCTION__, ERROR_INVALID_PARAMETER);
	return FALSE;
}

void CTcpServer::PrepareStart()
{
	m_bfActiveSockets.Reset(m_dwMaxConnectionCount);
	m_lsFreeSocket.Reset(m_dwFreeSocketObjPool);

	m_bfObjPool.SetItemCapacity(m_dwSocketBufferSize);
	m_bfObjPool.SetPoolSize(m_dwFreeBufferObjPool);
	m_bfObjPool.SetPoolHold(m_dwFreeBufferObjHold);

	m_bfObjPool.Prepare();
}

BOOL CTcpServer::CheckStarting()
{
	CSpinLock locallock(m_csState);

	if(m_enState == SS_STOPPED)
		m_enState = SS_STARTING;
	else
	{
		SetLastError(SE_ILLEGAL_STATE, __FUNCTION__, ERROR_INVALID_STATE);
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpServer::CheckStoping()
{
	if(m_enState != SS_STOPPED)
	{
		CSpinLock locallock(m_csState);

		if(HasStarted())
		{
			m_enState = SS_STOPPING;
			return TRUE;
		}
	}

	SetLastError(SE_ILLEGAL_STATE, __FUNCTION__, ERROR_INVALID_STATE);

	return FALSE;
}

BOOL CTcpServer::CreateListenSocket(LPCTSTR lpszBindAddress, USHORT usPort)
{
	BOOL isOK = FALSE;

	if(::IsStrEmpty(lpszBindAddress))
		lpszBindAddress = DEFAULT_IPV4_BIND_ADDRESS;

	HP_SOCKADDR addr;

	if(::sockaddr_A_2_IN(lpszBindAddress, usPort, addr))
	{
		m_usFamily = addr.family;
		m_soListen = socket(m_usFamily, SOCK_STREAM, IPPROTO_TCP);

		if(m_soListen != INVALID_SOCKET)
		{
			BOOL bOnOff	= (m_dwKeepAliveTime > 0 && m_dwKeepAliveInterval > 0);
			ENSURE(IS_NO_ERROR(::SSO_KeepAliveVals(m_soListen, bOnOff, m_dwKeepAliveTime, m_dwKeepAliveInterval)));
			ENSURE(IS_NO_ERROR(::SSO_ReuseAddress(m_soListen, m_enReusePolicy)));
			ENSURE(IS_NO_ERROR(::SSO_NoDelay(m_soListen, m_bNoDelay)));
			ENSURE(IS_NO_ERROR(::SSO_NoBlock(m_soListen)));
			ENSURE(addr.IsIPv4() || IS_NO_ERROR(::SSO_DualStack(m_soListen, m_bDualStack)));
			
			if(::bind(m_soListen, addr.Addr(), addr.AddrSize()) != SOCKET_ERROR)
			{
				if(TRIGGER(FirePrepareListen(m_soListen)) != HR_ERROR)
				{
					if(::listen(m_soListen, m_dwSocketListenQueue) != SOCKET_ERROR)
					{
						m_pfnAcceptEx				= ::Get_AcceptEx_FuncPtr(m_soListen);
						m_pfnGetAcceptExSockaddrs	= ::Get_GetAcceptExSockaddrs_FuncPtr(m_soListen);
						m_pfnDisconnectEx			= ::Get_DisconnectEx_FuncPtr(m_soListen);

						ASSERT(m_pfnAcceptEx);
						ASSERT(m_pfnGetAcceptExSockaddrs);
						ASSERT(m_pfnDisconnectEx);

						isOK = TRUE;
					}
					else
						SetLastError(SE_SOCKET_LISTEN, __FUNCTION__, ::WSAGetLastError());
				}
				else
					SetLastError(SE_SOCKET_PREPARE, __FUNCTION__, ENSURE_ERROR_CANCELLED);
			}
			else
				SetLastError(SE_SOCKET_BIND, __FUNCTION__, ::WSAGetLastError());
		}
		else
			SetLastError(SE_SOCKET_CREATE, __FUNCTION__, ::WSAGetLastError());
	}
	else
		SetLastError(SE_SOCKET_CREATE, __FUNCTION__, ::WSAGetLastError());

	return isOK;
}

BOOL CTcpServer::CreateCompletePort()
{
	m_hCompletePort	= ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	
	if(m_hCompletePort == nullptr)
		SetLastError(SE_CP_CREATE, __FUNCTION__, ::GetLastError());

	return (m_hCompletePort != nullptr);
}

BOOL CTcpServer::CreateWorkerThreads()
{
	for(DWORD i = 0; i < m_dwWorkerThreadCount; i++)
	{
		HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, WorkerThreadProc, (LPVOID)this, 0, nullptr);
		
		if(hThread)
			m_vtWorkerThreads.push_back(hThread);
		else
		{
			SetLastError(SE_WORKER_THREAD_CREATE, __FUNCTION__, ::GetLastError());
			return FALSE;
		}
	}

	if(IS_NULL(m_tqGC.CreateTimer(GCProc, this, GC_CHECK_INTERVAL, GC_CHECK_INTERVAL, WT_EXECUTEINTIMERTHREAD)))
	{
		SetLastError(SE_GC_START, __FUNCTION__, ::GetLastError());
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpServer::StartAccept()
{
	if(::CreateIoCompletionPort((HANDLE)m_soListen, m_hCompletePort, m_soListen, 0))
	{
		m_iRemainAcceptSockets = m_dwAcceptSocketCount;

		for(DWORD i = 0; i < m_dwAcceptSocketCount; i++)
			ENSURE(::PostIocpAccept(m_hCompletePort));
	}
	else
	{
		SetLastError(SE_SOCKE_ATTACH_TO_CP, __FUNCTION__, ::GetLastError());
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpServer::Stop()
{
	if(!CheckStoping())
		return FALSE;

	CloseListenSocket();

	WaitForAcceptSocketClose();

	DisconnectClientSocket();
	WaitForClientSocketClose();
	WaitForWorkerThreadEnd();
	
	ReleaseClientSocket();

	FireShutdown();

	ReleaseFreeSocket();
	ReleaseFreeBuffer();

	CloseCompletePort();

	Reset();

	return TRUE;
}

void CTcpServer::Reset()
{
	m_phSocket.Reset();

	m_iRemainAcceptSockets		= 0;
	m_pfnAcceptEx				= nullptr;
	m_pfnGetAcceptExSockaddrs	= nullptr;
	m_pfnDisconnectEx			= nullptr;
	m_enState					= SS_STOPPED;
	m_usFamily					= AF_UNSPEC;

	m_evWait.Set();
}

void CTcpServer::CloseListenSocket()
{
	if(m_soListen != INVALID_SOCKET)
	{
		::ManualCloseSocket(m_soListen);
		m_soListen = INVALID_SOCKET;
		
		::WaitWithMessageLoop(100);
	}
}

void CTcpServer::DisconnectClientSocket()
{
	if(m_bfActiveSockets.Elements() == 0)
		return;

	TSocketObjPtrPool::IndexSet indexes;
	m_bfActiveSockets.CopyIndexes(indexes);

	for(auto it = indexes.begin(), end = indexes.end(); it != end; ++it)
		Disconnect(*it);
}

void CTcpServer::ReleaseClientSocket()
{
	ENSURE(m_bfActiveSockets.IsEmpty());
	m_bfActiveSockets.Reset();
}

TSocketObj*	CTcpServer::GetFreeSocketObj(CONNID dwConnID, SOCKET soClient)
{
	DWORD dwIndex;
	TSocketObj* pSocketObj = nullptr;

	if(m_lsFreeSocket.TryLock(&pSocketObj, dwIndex))
	{
		if(::GetTimeGap32(pSocketObj->freeTime) >= m_dwFreeSocketObjLockTime)
			ENSURE(m_lsFreeSocket.ReleaseLock(nullptr, dwIndex));
		else
		{
			ENSURE(m_lsFreeSocket.ReleaseLock(pSocketObj, dwIndex));
			pSocketObj = nullptr;
		}
	}

	if(!pSocketObj) pSocketObj = CreateSocketObj();
	pSocketObj->Reset(dwConnID, soClient);

	return pSocketObj;
}

void CTcpServer::AddFreeSocketObj(TSocketObj* pSocketObj, EnSocketCloseFlag enFlag, EnSocketOperation enOperation, int iErrorCode)
{
	if(!InvalidSocketObj(pSocketObj))
		return;

	CloseClientSocketObj(pSocketObj, enFlag, enOperation, iErrorCode);

	m_bfActiveSockets.Remove(pSocketObj->connID);
	TSocketObj::Release(pSocketObj);

#ifndef USE_EXTERNAL_GC
	ReleaseGCSocketObj();
#endif
	
	if(!m_lsFreeSocket.TryPut(pSocketObj))
		m_lsGCSocket.PushBack(pSocketObj);
}

void CTcpServer::ReleaseGCSocketObj(BOOL bForce)
{
	::ReleaseGCObj(m_lsGCSocket, m_dwFreeSocketObjLockTime, bForce);
}

BOOL CTcpServer::InvalidSocketObj(TSocketObj* pSocketObj)
{
	return TSocketObj::InvalidSocketObj(pSocketObj);
}

void CTcpServer::AddClientSocketObj(CONNID dwConnID, TSocketObj* pSocketObj, const HP_SOCKADDR& remoteAddr)
{
	ASSERT(FindSocketObj(dwConnID) == nullptr);

	pSocketObj->connTime	= ::TimeGetTime();
	pSocketObj->activeTime	= pSocketObj->connTime;

	remoteAddr.Copy(pSocketObj->remoteAddr);
	pSocketObj->SetConnected();

	ENSURE(m_bfActiveSockets.ReleaseLock(dwConnID, pSocketObj));
}

void CTcpServer::ReleaseFreeSocket()
{
	m_tqGC.Reset();
	m_lsFreeSocket.Clear();

	ReleaseGCSocketObj(TRUE);
	ENSURE(m_lsGCSocket.IsEmpty());
}

TSocketObj* CTcpServer::CreateSocketObj()
{
	return TSocketObj::Construct(m_phSocket, m_bfObjPool);
}

void CTcpServer::DeleteSocketObj(TSocketObj* pSocketObj)
{
	TSocketObj::Destruct(pSocketObj);
}

TBufferObj* CTcpServer::GetFreeBufferObj(int iLen)
{
	ASSERT(iLen >= -1 && iLen <= (int)m_dwSocketBufferSize);

	TBufferObj* pBufferObj	= m_bfObjPool.PickFreeItem();
	if(iLen < 0) iLen		= m_dwSocketBufferSize;
	pBufferObj->buff.len	= iLen;

	return pBufferObj;
}

void CTcpServer::AddFreeBufferObj(TBufferObj* pBufferObj)
{
	m_bfObjPool.PutFreeItem(pBufferObj);
}

void CTcpServer::ReleaseFreeBuffer()
{
	m_bfObjPool.Clear();
}

TSocketObj* CTcpServer::FindSocketObj(CONNID dwConnID)
{
	TSocketObj* pSocketObj = nullptr;

	if(m_bfActiveSockets.Get(dwConnID, &pSocketObj) != TSocketObjPtrPool::GR_VALID)
		pSocketObj = nullptr;

	return pSocketObj;
}

void CTcpServer::CloseClientSocketObj(TSocketObj* pSocketObj, EnSocketCloseFlag enFlag, EnSocketOperation enOperation, int iErrorCode, int iShutdownFlag)
{
	ASSERT(TSocketObj::IsExist(pSocketObj));

	if(enFlag == SCF_CLOSE)
		TriggerFireClose(pSocketObj, SO_CLOSE, SE_OK);
	else if(enFlag == SCF_ERROR)
		TriggerFireClose(pSocketObj, enOperation, iErrorCode);

	SOCKET socket = pSocketObj->socket;
	pSocketObj->socket = INVALID_SOCKET;

	::ManualCloseSocket(socket, iShutdownFlag);
}

BOOL CTcpServer::GetListenAddress(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)
{
	ASSERT(lpszAddress != nullptr && iAddressLen > 0);

	return ::GetSocketLocalAddress(m_soListen, lpszAddress, iAddressLen, usPort);
}

BOOL CTcpServer::GetLocalAddress(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)
{
	ASSERT(lpszAddress != nullptr && iAddressLen > 0);

	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	return ::GetSocketLocalAddress(pSocketObj->socket, lpszAddress, iAddressLen, usPort);
}

BOOL CTcpServer::GetRemoteAddress(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)
{
	ASSERT(lpszAddress != nullptr && iAddressLen > 0);

	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsExist(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	ADDRESS_FAMILY usFamily;
	return ::sockaddr_IN_2_A(pSocketObj->remoteAddr, usFamily, lpszAddress, iAddressLen, usPort);
}

BOOL CTcpServer::SetConnectionExtra(CONNID dwConnID, PVOID pExtra)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return SetConnectionExtra(pSocketObj, pExtra);
}

BOOL CTcpServer::SetConnectionExtra(TSocketObj* pSocketObj, PVOID pExtra)
{
	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		pSocketObj->extra = pExtra;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::GetConnectionExtra(CONNID dwConnID, PVOID* ppExtra)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return GetConnectionExtra(pSocketObj, ppExtra);
}

BOOL CTcpServer::GetConnectionExtra(TSocketObj* pSocketObj, PVOID* ppExtra)
{
	ASSERT(ppExtra != nullptr);

	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		*ppExtra = pSocketObj->extra;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::SetConnectionReserved(CONNID dwConnID, PVOID pReserved)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return SetConnectionReserved(pSocketObj, pReserved);
}

BOOL CTcpServer::SetConnectionReserved(TSocketObj* pSocketObj, PVOID pReserved)
{
	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		pSocketObj->reserved = pReserved;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::GetConnectionReserved(CONNID dwConnID, PVOID* ppReserved)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return GetConnectionReserved(pSocketObj, ppReserved);
}

BOOL CTcpServer::GetConnectionReserved(TSocketObj* pSocketObj, PVOID* ppReserved)
{
	ASSERT(ppReserved != nullptr);

	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		*ppReserved = pSocketObj->reserved;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::SetConnectionReserved2(CONNID dwConnID, PVOID pReserved2)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return SetConnectionReserved2(pSocketObj, pReserved2);
}

BOOL CTcpServer::SetConnectionReserved2(TSocketObj* pSocketObj, PVOID pReserved2)
{
	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		pSocketObj->reserved2 = pReserved2;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::GetConnectionReserved2(CONNID dwConnID, PVOID* ppReserved2)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);
	return GetConnectionReserved2(pSocketObj, ppReserved2);
}

BOOL CTcpServer::GetConnectionReserved2(TSocketObj* pSocketObj, PVOID* ppReserved2)
{
	ASSERT(ppReserved2 != nullptr);

	if(!TSocketObj::IsExist(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		*ppReserved2 = pSocketObj->reserved2;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::IsPauseReceive(CONNID dwConnID, BOOL& bPaused)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		bPaused = pSocketObj->paused;
		return TRUE;
	}

	return FALSE;
}

BOOL CTcpServer::IsConnected(CONNID dwConnID)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	return pSocketObj->HasConnected();
}

BOOL CTcpServer::GetPendingDataLength(CONNID dwConnID, int& iPending)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
	else
	{
		iPending = pSocketObj->Pending();
		return TRUE;
	}

	return FALSE;
}

DWORD CTcpServer::GetConnectionCount()
{
	return m_bfActiveSockets.Elements();
}

BOOL CTcpServer::GetAllConnectionIDs(CONNID pIDs[], DWORD& dwCount)
{
	return m_bfActiveSockets.GetAllElementIndexes(pIDs, dwCount);
}

BOOL CTcpServer::GetConnectPeriod(CONNID dwConnID, DWORD& dwPeriod)
{
	BOOL isOK				= TRUE;
	TSocketObj* pSocketObj	= FindSocketObj(dwConnID);

	if(TSocketObj::IsValid(pSocketObj))
		dwPeriod = ::GetTimeGap32(pSocketObj->connTime);
	else
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		isOK = FALSE;
	}

	return isOK;
}

BOOL CTcpServer::GetSilencePeriod(CONNID dwConnID, DWORD& dwPeriod)
{
	if(!m_bMarkSilence)
		return FALSE;

	BOOL isOK				= TRUE;
	TSocketObj* pSocketObj	= FindSocketObj(dwConnID);

	if(TSocketObj::IsValid(pSocketObj))
		dwPeriod = ::GetTimeGap32(pSocketObj->activeTime);
	else
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		isOK = FALSE;
	}

	return isOK;
}

BOOL CTcpServer::Disconnect(CONNID dwConnID, BOOL bForce)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	return ::PostIocpDisconnect(m_hCompletePort, dwConnID);
}

BOOL CTcpServer::DisconnectLongConnections(DWORD dwPeriod, BOOL bForce)
{
	if(dwPeriod > MAX_CONNECTION_PERIOD)
		return FALSE;
	if(m_bfActiveSockets.Elements() == 0)
		return TRUE;

	DWORD now = ::TimeGetTime();

	TSocketObjPtrPool::IndexSet indexes;
	m_bfActiveSockets.CopyIndexes(indexes);

	for(auto it = indexes.begin(), end = indexes.end(); it != end; ++it)
	{
		CONNID connID			= *it;
		TSocketObj* pSocketObj	= FindSocketObj(connID);

		if(TSocketObj::IsValid(pSocketObj) && (int)(now - pSocketObj->connTime) >= (int)dwPeriod)
			Disconnect(connID, bForce);
	}

	return TRUE;
}

BOOL CTcpServer::DisconnectSilenceConnections(DWORD dwPeriod, BOOL bForce)
{
	if(!m_bMarkSilence)
		return FALSE;
	if(dwPeriod > MAX_CONNECTION_PERIOD)
		return FALSE;
	if(m_bfActiveSockets.Elements() == 0)
		return TRUE;
	
	DWORD now = ::TimeGetTime();

	TSocketObjPtrPool::IndexSet indexes;
	m_bfActiveSockets.CopyIndexes(indexes);

	for(auto it = indexes.begin(), end = indexes.end(); it != end; ++it)
	{
		CONNID connID			= *it;
		TSocketObj* pSocketObj	= FindSocketObj(connID);

		if(TSocketObj::IsValid(pSocketObj) && (int)(now - pSocketObj->activeTime) >= (int)dwPeriod)
			Disconnect(connID, bForce);
	}

	return TRUE;
}

void CTcpServer::WaitForAcceptSocketClose()
{
	while(m_iRemainAcceptSockets > 0)
		::WaitWithMessageLoop(50);
}

void CTcpServer::WaitForClientSocketClose()
{
	while(m_bfActiveSockets.Elements() > 0)
		::WaitWithMessageLoop(50);
}

void CTcpServer::WaitForWorkerThreadEnd()
{
	int count = (int)m_vtWorkerThreads.size();

	for(int i = 0; i < count; i++)
		::PostIocpExit(m_hCompletePort);

	int remain	= count;
	int index	= 0;

	while(remain > 0)
	{
		int wait = min(remain, MAXIMUM_WAIT_OBJECTS);
		HANDLE* pHandles = CreateLocalObjects(HANDLE, wait);

		for(int i = 0; i < wait; i++)
			pHandles[i]	= m_vtWorkerThreads[i + index];

		ENSURE(::WaitForMultipleObjects((DWORD)wait, pHandles, TRUE, INFINITE) == WAIT_OBJECT_0);

		for(int i = 0; i < wait; i++)
			::CloseHandle(pHandles[i]);

		remain	-= wait;
		index	+= wait;
	}

	m_vtWorkerThreads.clear();
}

void CTcpServer::CloseCompletePort()
{
	if(m_hCompletePort != nullptr)
	{
		::CloseHandle(m_hCompletePort);
		m_hCompletePort = nullptr;
	}
}

BOOL CTcpServer::DoAccept()
{
	BOOL isOK = FALSE;

	if(HasStarted())
	{
		SOCKET		soClient	= socket(m_usFamily, SOCK_STREAM, IPPROTO_TCP);
		TBufferObj*	pBufferObj	= GetFreeBufferObj();

		ASSERT(soClient != INVALID_SOCKET);

		isOK = IS_NO_ERROR(::PostAccept(m_pfnAcceptEx, m_soListen, soClient, pBufferObj, m_usFamily));

		if(!isOK)
		{
			ENSURE(!HasStarted());

			::ManualCloseSocket(soClient);
			AddFreeBufferObj(pBufferObj);
		}
	}

	if(!isOK)
	{
		::InterlockedDecrement(&m_iRemainAcceptSockets);
		ASSERT(m_iRemainAcceptSockets >= 0);
	}

	return isOK;
}

UINT WINAPI CTcpServer::WorkerThreadProc(LPVOID pv)
{
	::SetCurrentWorkerThreadName();

	CTcpServer* pServer = (CTcpServer*)pv;
	pServer->OnWorkerThreadStart(SELF_THREAD_ID);

	while(TRUE)
	{
		DWORD dwErrorCode = NO_ERROR;

		DWORD dwBytes;
		OVERLAPPED* pOverlapped;
		TSocketObj* pSocketObj;
		
		BOOL result = ::GetQueuedCompletionStatus
												(
													pServer->m_hCompletePort,
													&dwBytes,
													(PULONG_PTR)&pSocketObj,
													&pOverlapped,
													INFINITE
												);

		if(pOverlapped == nullptr)
		{
			EnIocpAction action = pServer->CheckIocpCommand(pOverlapped, dwBytes, (ULONG_PTR)pSocketObj);

			if(action == IOCP_ACT_CONTINUE)
				continue;
			else if(action == IOCP_ACT_BREAK)
				break;
		}

		TBufferObj* pBufferObj	= CONTAINING_RECORD(pOverlapped, TBufferObj, ov);
		CONNID dwConnID			= pBufferObj->operation != SO_ACCEPT ? pSocketObj->connID : 0;

		if (!result)
		{
			DWORD dwFlag	= 0;
			DWORD dwSysCode = ::GetLastError();
			dwErrorCode		= dwSysCode;

			if(pServer->HasStarted())
			{
				SOCKET sock	= pBufferObj->operation != SO_ACCEPT ? pBufferObj->client : (SOCKET)pSocketObj;

				if (!::WSAGetOverlappedResult(sock, &pBufferObj->ov, &dwBytes, FALSE, &dwFlag))
				{
					dwErrorCode = ::WSAGetLastError();
					TRACE("GetQueuedCompletionStatus error (<S-CNNID: %Iu> SYS: %d, SOCK: %d, FLAG: %d)\n", dwConnID, dwSysCode, dwErrorCode, dwFlag);
				}
			}

			ASSERT(dwSysCode != NO_ERROR && dwErrorCode != NO_ERROR);
		}

		pServer->HandleIo(dwConnID, pSocketObj, pBufferObj, dwBytes, dwErrorCode);
	}

	pServer->OnWorkerThreadEnd(SELF_THREAD_ID);

	return 0;
}

EnIocpAction CTcpServer::CheckIocpCommand(OVERLAPPED* pOverlapped, DWORD dwBytes, ULONG_PTR ulCompKey)
{
	ASSERT(pOverlapped == nullptr);

	EnIocpAction action = IOCP_ACT_CONTINUE;
	CONNID dwConnID		= (CONNID)ulCompKey;

	switch(dwBytes)
	{
	case IOCP_CMD_SEND		: DoSend(dwConnID)			; break;
	case IOCP_CMD_UNPAUSE	: DoUnpause(dwConnID)		; break;
	case IOCP_CMD_ACCEPT	: DoAccept()				; break;
	case IOCP_CMD_DISCONNECT: ForceDisconnect(dwConnID)	; break;
	case IOCP_CMD_EXIT		: action = IOCP_ACT_BREAK	; break;
	default					: CheckError(FindSocketObj(dwConnID), SO_CLOSE, (int)dwBytes);
	}

	return action;
}

void CTcpServer::ForceDisconnect(CONNID dwConnID)
{
	AddFreeSocketObj(FindSocketObj(dwConnID), SCF_CLOSE);
}

void CTcpServer::HandleIo(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj, DWORD dwBytes, DWORD dwErrorCode)
{
	ASSERT(pBufferObj != nullptr);
	ASSERT(pSocketObj != nullptr);

	EnSocketOperation enOperation = pBufferObj->operation;

	if(dwErrorCode != NO_ERROR)
	{
		HandleError(dwConnID, pSocketObj, pBufferObj, dwErrorCode);

		goto END_HANDLE_IO;
	}

	if(dwBytes == 0 && enOperation != SO_ACCEPT)
	{
		AddFreeSocketObj(pSocketObj, SCF_CLOSE);
		AddFreeBufferObj(pBufferObj);

		goto END_HANDLE_IO;
	}

	pBufferObj->buff.len = dwBytes;

	switch(enOperation)
	{
	case SO_ACCEPT:
		HandleAccept((SOCKET)pSocketObj, pBufferObj);
		break;
	case SO_SEND:
		HandleSend(dwConnID, pSocketObj, pBufferObj);
		break;
	case SO_RECEIVE:
		HandleReceive(dwConnID, pSocketObj, pBufferObj);
		break;
	default:
		ASSERT(FALSE);
	}

END_HANDLE_IO:

	if(enOperation != SO_ACCEPT)
		pSocketObj->Decrement();
}

void CTcpServer::HandleError(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj, DWORD dwErrorCode)
{
	if(pBufferObj->operation != SO_ACCEPT)
		CheckError(pSocketObj, pBufferObj->operation, dwErrorCode);
	else
	{
		::ManualCloseSocket(pBufferObj->client);
		ENSURE(::PostIocpAccept(m_hCompletePort));
	}

	if(pBufferObj->operation != SO_SEND || pBufferObj->ReleaseSendCounter() == 0)
		AddFreeBufferObj(pBufferObj);
}

void CTcpServer::HandleAccept(SOCKET soListen, TBufferObj* pBufferObj)
{
	ENSURE(::PostIocpAccept(m_hCompletePort));

	int iLocalSockaddrLen;
	int iRemoteSockaddrLen;
	HP_PSOCKADDR pLocalSockAddr;
	HP_PSOCKADDR pRemoteSockAddr;

	int iAddrLen = HP_SOCKADDR::AddrSize(m_usFamily) + 16;

	m_pfnGetAcceptExSockaddrs
							(
								pBufferObj->buff.buf,
								0,
								iAddrLen,
								iAddrLen,
								(SOCKADDR**)&pLocalSockAddr,
								&iLocalSockaddrLen,
								(SOCKADDR**)&pRemoteSockAddr,
								&iRemoteSockaddrLen
							);

	CONNID dwConnID = 0;
	SOCKET socket	= pBufferObj->client;

	if(!HasStarted() || !m_bfActiveSockets.AcquireLock(dwConnID))
	{
		::ManualCloseSocket(socket, SD_BOTH);
		AddFreeBufferObj(pBufferObj);

		return;
	}

	TSocketObj* pSocketObj = GetFreeSocketObj(dwConnID, socket);
	pSocketObj->csRecv.Lock();

	AddClientSocketObj(dwConnID, pSocketObj, *pRemoteSockAddr);

	CLocalSafeCounter localcounter(*pSocketObj);

	::SSO_UpdateAcceptContext(socket, soListen);
	::CreateIoCompletionPort((HANDLE)socket, m_hCompletePort, (ULONG_PTR)pSocketObj, 0);

	if(TriggerFireAccept(pSocketObj) != HR_ERROR)
		DoReceive(pSocketObj, pBufferObj);
	else
	{
		AddFreeSocketObj(pSocketObj, SCF_NONE);
		AddFreeBufferObj(pBufferObj);
	}
}

void CTcpServer::HandleSend(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	if(TSocketObj::IsValid(pSocketObj))
	{
		long iLength = -(long)(pBufferObj->buff.len);
		
		switch(m_enSendPolicy)
		{
		case SP_PACK:
			::InterlockedExchangeAdd(&pSocketObj->sndCount, iLength);
			TriggerFireSend(pSocketObj, pBufferObj);
			DoSendPack(pSocketObj);
			break;
		case SP_SAFE:
			::InterlockedExchangeAdd(&pSocketObj->sndCount, iLength);
			TriggerFireSend(pSocketObj, pBufferObj);
			DoSendSafe(pSocketObj);
			break;
		case SP_DIRECT:
			::InterlockedExchangeAdd(&pSocketObj->pending, iLength);
			TriggerFireSend(pSocketObj, pBufferObj);
			break;
		default:
			ASSERT(FALSE);
		}
	}

	if(pBufferObj->ReleaseSendCounter() == 0)
		AddFreeBufferObj(pBufferObj);
}

void CTcpServer::HandleReceive(CONNID dwConnID, TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	EnHandleResult hr = TSocketObj::IsValid(pSocketObj) ? HR_OK : (EnHandleResult)HR_CLOSED;

	if(hr == HR_OK)
	{
		if(m_bMarkSilence) pSocketObj->activeTime = ::TimeGetTime();

		hr = TriggerFireReceive(pSocketObj, pBufferObj);

		if(hr == HR_OK || hr == HR_IGNORE)
		{
			if(::ContinueReceive(this, pSocketObj, pBufferObj, hr))
			{
				{
					CSpinLock locallock(pSocketObj->sgPause);

					pSocketObj->recving = FALSE;
				}

				DoReceive(pSocketObj, pBufferObj);
			}
		}
	}

	if(hr == HR_CLOSED)
	{
		AddFreeBufferObj(pBufferObj);
	}
	else if(hr == HR_ERROR)
	{
		TRACE("<S-CNNID: %Iu> OnReceive() event return 'HR_ERROR', connection will be closed !\n", dwConnID);

		AddFreeSocketObj(pSocketObj, SCF_ERROR, SO_RECEIVE, ENSURE_ERROR_CANCELLED);
		AddFreeBufferObj(pBufferObj);
	}
}

int CTcpServer::DoUnpause(CONNID dwConnID)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
		return ERROR_OBJECT_NOT_FOUND;

	EnHandleResult hr = BeforeUnpause(pSocketObj);

	if(hr != HR_OK && hr != HR_IGNORE)
	{
		if(hr == HR_ERROR)
			AddFreeSocketObj(pSocketObj, SCF_ERROR, SO_RECEIVE, ENSURE_ERROR_CANCELLED);

		return ERROR_CANCELLED;
	}

	return DoReceive(pSocketObj, GetFreeBufferObj());
}

int CTcpServer::DoReceive(TSocketObj* pSocketObj, TBufferObj* pBufferObj)
{
	int result		= NO_ERROR;
	BOOL bNeedFree	= FALSE;

	{
		CSpinLock locallock(pSocketObj->sgPause);

		if(pSocketObj->paused || pSocketObj->recving)
			bNeedFree = TRUE;
		else
		{
			pSocketObj->recving	 = TRUE;
			pBufferObj->buff.len = m_dwSocketBufferSize;

			result = ::PostReceive(pSocketObj, pBufferObj);
		}
	}

	if(result != NO_ERROR)
	{
		CheckError(pSocketObj, SO_RECEIVE, result);
		bNeedFree = TRUE;
	}

	if(bNeedFree) AddFreeBufferObj(pBufferObj);

	return result;
}

BOOL CTcpServer::PauseReceive(CONNID dwConnID, BOOL bPause)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	{
		CSpinLock locallock(pSocketObj->sgPause);

		if(pSocketObj->paused == bPause)
			return TRUE;

		pSocketObj->paused = bPause;
	}

	if(!bPause) PostIocpUnpause(m_hCompletePort, dwConnID);

	return TRUE;
}

BOOL CTcpServer::Send(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset)
{
	ASSERT(pBuffer && iLength > 0);

	if(iOffset != 0) pBuffer += iOffset;

	WSABUF buffer;
	buffer.len = iLength;
	buffer.buf = (char*)pBuffer;

	return SendPackets(dwConnID, &buffer, 1);
}

BOOL CTcpServer::DoSendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount)
{
	ASSERT(pBuffers && iCount > 0);

	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
	{
		::SetLastError(ERROR_OBJECT_NOT_FOUND);
		return FALSE;
	}

	return DoSendPackets(pSocketObj, pBuffers, iCount);
}

BOOL CTcpServer::DoSendPackets(TSocketObj* pSocketObj, const WSABUF pBuffers[], int iCount)
{
	ASSERT(pSocketObj && pBuffers && iCount > 0);

	int result = NO_ERROR;

	if(pBuffers && iCount > 0)
	{
		CLocalSafeCounter localcounter(*pSocketObj);
		CCriSecLock locallock(pSocketObj->csSend);

		if(TSocketObj::IsValid(pSocketObj))
			result = SendInternal(pSocketObj, pBuffers, iCount);
		else
			result = ERROR_OBJECT_NOT_FOUND;
	}
	else
		result = ERROR_INVALID_PARAMETER;

	if(result != NO_ERROR)
	{
		if(m_enSendPolicy == SP_DIRECT && TSocketObj::IsValid(pSocketObj))
			::PostIocpClose(m_hCompletePort, pSocketObj->connID, result);

		::SetLastError(result);
	}

	return (result == NO_ERROR);
}

int CTcpServer::SendInternal(TSocketObj* pSocketObj, const WSABUF pBuffers[], int iCount)
{
	int result = NO_ERROR;

	for(int i = 0; i < iCount; i++)
	{
		int iBufLen = pBuffers[i].len;

		if(iBufLen > 0)
		{
			BYTE* pBuffer = (BYTE*)pBuffers[i].buf;
			ASSERT(pBuffer);

			switch(m_enSendPolicy)
			{
			case SP_PACK:	result = SendPack(pSocketObj, pBuffer, iBufLen);	break;
			case SP_SAFE:	result = SendSafe(pSocketObj, pBuffer, iBufLen);	break;
			case SP_DIRECT:	result = SendDirect(pSocketObj, pBuffer, iBufLen);	break;
			default: ASSERT(FALSE);	result = ERROR_INVALID_INDEX;				break;
			}

			if(result != NO_ERROR)
				break;
		}
	}

	return result;
}

int CTcpServer::SendPack(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength)
{
	return CatAndPost(pSocketObj, pBuffer, iLength);
}

int CTcpServer::SendSafe(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength)
{
	return CatAndPost(pSocketObj, pBuffer, iLength);
}

int CTcpServer::CatAndPost(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength)
{
	int result = NO_ERROR;

	pSocketObj->sndBuff.Cat(pBuffer, iLength);
	pSocketObj->pending += iLength;

	ASSERT(pSocketObj->pending > 0);

	if(pSocketObj->IsCanSend() && pSocketObj->IsSmooth() && !::PostIocpSend(m_hCompletePort, pSocketObj->connID))
		result = ::GetLastError();

	return result;
}

int CTcpServer::SendDirect(TSocketObj* pSocketObj, const BYTE* pBuffer, int iLength)
{
	int result	= NO_ERROR;
	int iRemain	= iLength;

	while(iRemain > 0)
	{
		int iBufferSize = min(iRemain, (int)m_dwSocketBufferSize);
		TBufferObj* pBufferObj = GetFreeBufferObj(iBufferSize);
		memcpy(pBufferObj->buff.buf, pBuffer, iBufferSize);

		::InterlockedExchangeAdd(&pSocketObj->pending, iBufferSize);

		result			= ::PostSend(pSocketObj, pBufferObj);
		LONG sndCounter	= pBufferObj->ReleaseSendCounter();

		if(sndCounter == 0 || result != NO_ERROR)
		{
			AddFreeBufferObj(pBufferObj);
			
			if(result != NO_ERROR)
			{
				::InterlockedExchangeAdd(&pSocketObj->pending, -iBufferSize);

				break;
			}
		}

		iRemain -= iBufferSize;
		pBuffer += iBufferSize;
	}

	return result;
}

int CTcpServer::DoSend(CONNID dwConnID)
{
	TSocketObj* pSocketObj = FindSocketObj(dwConnID);

	if(!TSocketObj::IsValid(pSocketObj))
		return ERROR_OBJECT_NOT_FOUND;

	CLocalSafeCounter localcounter(*pSocketObj);

	switch(m_enSendPolicy)
	{
	case SP_PACK:			return DoSendPack(pSocketObj);
	case SP_SAFE:			return DoSendSafe(pSocketObj);
	default: ASSERT(FALSE);	return ERROR_INVALID_INDEX;
	}
}

int CTcpServer::DoSendPack(TSocketObj* pSocketObj)
{
	if(!pSocketObj->IsCanSend())
		return NO_ERROR;

	int result = NO_ERROR;

	if(pSocketObj->IsPending() && pSocketObj->TurnOffSmooth())
	{
		{
			CCriSecLock locallock(pSocketObj->csSend);

			if(!TSocketObj::IsValid(pSocketObj))
				return ERROR_OBJECT_NOT_FOUND;

			if(pSocketObj->IsPending())
				result = SendItem(pSocketObj);

			pSocketObj->TurnOnSmooth();
		}

		if(result == WSA_IO_PENDING && pSocketObj->IsSmooth())
			::PostIocpSend(m_hCompletePort, pSocketObj->connID);
	}

	if(!IOCP_SUCCESS(result))
		CheckError(pSocketObj, SO_SEND, result);

	return result;
}

int CTcpServer::DoSendSafe(TSocketObj* pSocketObj)
{
	long lSendBuffSize = pSocketObj->GetSendBufferSize();

	if(pSocketObj->sndCount < lSendBuffSize && !pSocketObj->IsSmooth())
	{
		CCriSecLock locallock(pSocketObj->csSend);

		if(!TSocketObj::IsValid(pSocketObj))
			return ERROR_OBJECT_NOT_FOUND;

		if(pSocketObj->sndCount < lSendBuffSize)
			pSocketObj->smooth = TRUE;
	}

	int result = NO_ERROR;

	if(pSocketObj->IsPending() && pSocketObj->IsSmooth())
	{
		CCriSecLock locallock(pSocketObj->csSend);

		if(!TSocketObj::IsValid(pSocketObj))
			return ERROR_OBJECT_NOT_FOUND;

		if(pSocketObj->IsPending() && pSocketObj->IsSmooth())
		{
			pSocketObj->smooth = FALSE;

			result = SendItem(pSocketObj);

			if(result == NO_ERROR)
				pSocketObj->smooth = TRUE;
		}
	}

	if(!IOCP_SUCCESS(result))
		CheckError(pSocketObj, SO_SEND, result);

	return result;
}

int CTcpServer::SendItem(TSocketObj* pSocketObj)
{
	int result = NO_ERROR;

	while(pSocketObj->sndBuff.Size() > 0)
	{
		TBufferObj* pBufferObj	= pSocketObj->sndBuff.PopFront();
		int iBufferSize			= pBufferObj->buff.len;

		ASSERT(iBufferSize > 0 && iBufferSize <= (int)m_dwSocketBufferSize);

		pSocketObj->pending	   -= iBufferSize;
		::InterlockedExchangeAdd(&pSocketObj->sndCount, iBufferSize);

		result			= ::PostSendNotCheck(pSocketObj, pBufferObj);
		LONG sndCounter	= pBufferObj->ReleaseSendCounter();

		if(sndCounter == 0 || !IOCP_SUCCESS(result))
			AddFreeBufferObj(pBufferObj);

		if(result != NO_ERROR)
			break;
	}

	return result;
}

BOOL CTcpServer::SendSmallFile(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead, const LPWSABUF pTail)
{
	CAtlFile file;
	CAtlFileMapping<> fmap;
	WSABUF szBuf[3];

	HRESULT hr = ::MakeSmallFilePackage(lpszFileName, file, fmap, szBuf, pHead, pTail);

	if(FAILED(hr))
	{
		::SetLastError(HRESULT_CODE(hr));
		return FALSE;
	}

	return SendPackets(dwConnID, szBuf, 3);
}

void CTcpServer::CheckError(TSocketObj* pSocketObj, EnSocketOperation enOperation, int iErrorCode)
{
	if(iErrorCode != WSAENOTSOCK && iErrorCode != ERROR_OPERATION_ABORTED)
		AddFreeSocketObj(pSocketObj, SCF_ERROR, enOperation, iErrorCode);
}

void WINAPI CTcpServer::GCProc(LPVOID pv, BOOLEAN bTimerFired)
{
	CTcpServer* pThis = (CTcpServer*)pv;
	pThis->ReleaseGCSocketObj(FALSE);
}


/* ========================================================================== */
/*  TcpClient.cpp
/*  source: Windows\Src\TcpClient.cpp
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "TcpClient.h" */
/* [amalgamated] #include "Common/WaitFor.h" */

#include <process.h>

const CInitSocket CTcpClient::sm_wsSocket;

BOOL CTcpClient::Start(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect, LPCTSTR lpszBindAddress, USHORT usLocalPort)
{
	if(!CheckParams() || !CheckStarting())
		return FALSE;

	PrepareStart();
	m_ccContext.Reset();

	BOOL isOK = FALSE;

	HP_SOCKADDR addrRemote, addrBind;

	if(CreateClientSocket(lpszRemoteAddress, addrRemote, usPort, lpszBindAddress, addrBind))
	{
		if(BindClientSocket(addrBind, addrRemote, usLocalPort))
		{
			if(TRIGGER(FirePrepareConnect(m_soClient)) != HR_ERROR)
			{
				if(ConnectToServer(addrRemote, bAsyncConnect))
				{
					if(CreateWorkerThread())
					{
						isOK = TRUE;
						m_evWait.Reset();
					}
					else
						SetLastError(SE_WORKER_THREAD_CREATE, __FUNCTION__, ERROR_CREATE_FAILED);
				}
				else
					SetLastError(SE_CONNECT_SERVER, __FUNCTION__, ::WSAGetLastError());
			}
			else
				SetLastError(SE_SOCKET_PREPARE, __FUNCTION__, ENSURE_ERROR_CANCELLED);
		}
		else
			SetLastError(SE_SOCKET_BIND, __FUNCTION__, ::WSAGetLastError());
	}
	else
		SetLastError(SE_SOCKET_CREATE, __FUNCTION__, ::WSAGetLastError());

	if(!isOK)
	{
		m_ccContext.Reset(FALSE);
		EXECUTE_RESTORE_ERROR(Stop());
	}

	return isOK;
}

BOOL CTcpClient::CheckParams()
{
	if	(((int)m_dwSyncConnectTimeout > 0)									&&
		((int)m_dwSocketBufferSize > 0)										&&
		((int)m_dwFreeBufferPoolSize >= 0)									&&
		((int)m_dwFreeBufferPoolHold >= 0)									&&
		((int)m_dwKeepAliveTime >= 1000 || m_dwKeepAliveTime == 0)			&&
		((int)m_dwKeepAliveInterval >= 1000 || m_dwKeepAliveInterval == 0)	)
		return TRUE;

	SetLastError(SE_INVALID_PARAM, __FUNCTION__, ERROR_INVALID_PARAMETER);
	return FALSE;
}

void CTcpClient::PrepareStart()
{
	m_itPool.SetItemCapacity((int)m_dwSocketBufferSize);
	m_itPool.SetPoolSize((int)m_dwFreeBufferPoolSize);
	m_itPool.SetPoolHold((int)m_dwFreeBufferPoolHold);

	m_itPool.Prepare();
}

BOOL CTcpClient::CheckStarting()
{
	CSpinLock locallock(m_csState);

	if(m_enState == SS_STOPPED)
		m_enState = SS_STARTING;
	else
	{
		SetLastError(SE_ILLEGAL_STATE, __FUNCTION__, ERROR_INVALID_STATE);
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpClient::CheckStoping(DWORD dwCurrentThreadID)
{
	if(m_enState != SS_STOPPED)
	{
		CSpinLock locallock(m_csState);

		if(HasStarted())
		{
			m_enState = SS_STOPPING;
			return TRUE;
		}
	}

	SetLastError(SE_ILLEGAL_STATE, __FUNCTION__, ERROR_INVALID_STATE);

	return FALSE;
}

BOOL CTcpClient::CreateClientSocket(LPCTSTR lpszRemoteAddress, HP_SOCKADDR& addrRemote, USHORT usPort, LPCTSTR lpszBindAddress, HP_SOCKADDR& addrBind)
{
	if(::IsStrNotEmpty(lpszBindAddress))
	{
		if(!::sockaddr_A_2_IN(lpszBindAddress, 0, addrBind))
			return FALSE;
	}

	HP_SCOPE_HOST host(lpszRemoteAddress);

	if(!::GetSockAddrByHostName(host.addr, usPort, addrRemote, addrBind.family))
		return FALSE;

	m_soClient = socket(addrRemote.family, SOCK_STREAM, IPPROTO_TCP);

	if(m_soClient == INVALID_SOCKET)
		return FALSE;

	BOOL bOnOff	= (m_dwKeepAliveTime > 0 && m_dwKeepAliveInterval > 0);
	ENSURE(::SSO_KeepAliveVals(m_soClient, bOnOff, m_dwKeepAliveTime, m_dwKeepAliveInterval) == NO_ERROR);
	ENSURE(::SSO_ReuseAddress(m_soClient, m_enReusePolicy) == NO_ERROR);
	ENSURE(::SSO_NoDelay(m_soClient, m_bNoDelay) == NO_ERROR);

	m_evSocket = ::WSACreateEvent();
	ASSERT(m_evSocket != WSA_INVALID_EVENT);

	SetRemoteHost(host.name, usPort);

	return TRUE;
}

BOOL CTcpClient::BindClientSocket(const HP_SOCKADDR& addrBind, const HP_SOCKADDR& addrRemote, USHORT usLocalPort)
{
	if(addrBind.IsSpecified() && usLocalPort == 0)
	{
		if(::bind(m_soClient, addrBind.Addr(), addrBind.AddrSize()) == SOCKET_ERROR)
			return FALSE;
	}
	else if(usLocalPort != 0)
	{
		HP_SOCKADDR realBindAddr = addrBind.IsSpecified() ? addrBind : HP_SOCKADDR::AnyAddr(addrRemote.family);

		realBindAddr.SetPort(usLocalPort);

		if(::bind(m_soClient, realBindAddr.Addr(), realBindAddr.AddrSize()) == SOCKET_ERROR)
			return FALSE;
	}

	m_dwConnID = ::GenerateConnectionID();

	return TRUE;
}

BOOL CTcpClient::ConnectToServer(const HP_SOCKADDR& addrRemote, BOOL bAsyncConnect)
{
	BOOL isOK = FALSE;

	if(bAsyncConnect)
	{
		if(::WSAEventSelect(m_soClient, m_evSocket, FD_CONNECT | FD_CLOSE) != SOCKET_ERROR)
		{
			int rc = ::connect(m_soClient, addrRemote.Addr(), addrRemote.AddrSize());
			isOK = (rc == NO_ERROR || (rc == SOCKET_ERROR && ::WSAGetLastError() == WSAEWOULDBLOCK));
		}
	}
	else
	{
		ENSURE(::SSO_NoBlock(m_soClient) == NO_ERROR);

		int rc = ::connect(m_soClient, addrRemote.Addr(), addrRemote.AddrSize());
		
		if(IS_NO_ERROR(rc) || IS_WOULDBLOCK_ERROR())
		{
			if(IS_HAS_ERROR(rc))
				rc = ::WaitForSocketWrite(m_soClient, m_dwSyncConnectTimeout);

			if(IS_NO_ERROR(rc))
			{
				if(::WSAEventSelect(m_soClient, m_evSocket, FD_READ | FD_WRITE | FD_CLOSE) != SOCKET_ERROR)
				{
					SetConnected();

					if(TRIGGER(FireConnect()) == HR_ERROR)
						::WSASetLastError(ENSURE_ERROR_CANCELLED);
					else
						isOK = TRUE;
				}
			}
			else
				::WSASetLastError(rc);
		}
	}

	return isOK;
}

BOOL CTcpClient::CreateWorkerThread()
{
	m_hWorker = (HANDLE)_beginthreadex(nullptr, 0, WorkerThreadProc, (LPVOID)this, 0, &m_dwWorkerID);

	return m_hWorker != nullptr;
}

UINT WINAPI CTcpClient::WorkerThreadProc(LPVOID pv)
{
	::SetCurrentWorkerThreadName();

	TRACE("---------------> Client Worker Thread 0x%08X started <---------------\n", SELF_THREAD_ID);

	CTcpClient* pClient	= (CTcpClient*)pv;
	pClient->OnWorkerThreadStart(SELF_THREAD_ID);

	BOOL bCallStop		= TRUE;
	HANDLE hEvents[]	= {pClient->m_evSocket, pClient->m_evBuffer, pClient->m_evWorker, pClient->m_evUnpause};
	
	pClient->m_rcBuffer.Malloc(pClient->m_dwSocketBufferSize);

	while(pClient->HasStarted())
	{
		DWORD retval = ::WSAWaitForMultipleEvents(ARRAY_SIZE(hEvents), hEvents, FALSE, WSA_INFINITE, FALSE);

		if(retval == WSA_WAIT_EVENT_0)
		{
			if(!pClient->ProcessNetworkEvent())
				break;
		}
		else if(retval == WSA_WAIT_EVENT_0 + 1)
		{
			if(!pClient->SendData())
				break;
		}
		else if(retval == WSA_WAIT_EVENT_0 + 2)
		{
			bCallStop = FALSE;
			break;
		}
		else if(retval == WSA_WAIT_EVENT_0 + 3)
		{
			if(!pClient->BeforeUnpause())
				break;

			if(!pClient->ReadData())
				break;
		}
		else if(retval == WSA_WAIT_FAILED)
		{
			pClient->m_ccContext.Reset(TRUE, SO_UNKNOWN, ::WSAGetLastError());
			break;
		}
		else
			ENSURE(FALSE);
	}

	pClient->OnWorkerThreadEnd(SELF_THREAD_ID);

	if(bCallStop && pClient->HasStarted())
		pClient->Stop();

	TRACE("---------------> Client Worker Thread 0x%08X stoped <---------------\n", SELF_THREAD_ID);

	return 0;
}

BOOL CTcpClient::ProcessNetworkEvent()
{
	BOOL bContinue = TRUE;
	WSANETWORKEVENTS events;
	
	int rc = ::WSAEnumNetworkEvents(m_soClient, m_evSocket, &events);

	if(rc == SOCKET_ERROR)
		bContinue = HandleError(events);

	if(!IsConnected() && bContinue && events.lNetworkEvents & FD_CONNECT)
		bContinue = HandleConnect(events);

	if(bContinue && events.lNetworkEvents & FD_READ)
		bContinue = HandleRead(events);

	if(bContinue && events.lNetworkEvents & FD_WRITE)
		bContinue = HandleWrite(events);

	if(bContinue && events.lNetworkEvents & FD_CLOSE)
		bContinue = HandleClose(events);

	return bContinue;
}

BOOL CTcpClient::HandleError(WSANETWORKEVENTS& events)
{
	int iCode						= ::WSAGetLastError();
	EnSocketOperation enOperation	= SO_UNKNOWN;

	if(events.lNetworkEvents & FD_CONNECT)
		enOperation = SO_CONNECT;
	else if(events.lNetworkEvents & FD_CLOSE)
		enOperation = SO_CLOSE;
	else if(events.lNetworkEvents & FD_READ)
		enOperation = SO_RECEIVE;
	else if(events.lNetworkEvents & FD_WRITE)
		enOperation = SO_SEND;

	ENSURE(::WSAResetEvent(m_evSocket));
	m_ccContext.Reset(TRUE, enOperation, iCode);

	return FALSE;
}

BOOL CTcpClient::HandleRead(WSANETWORKEVENTS& events)
{
	BOOL bContinue	= TRUE;
	int iCode		= events.iErrorCode[FD_READ_BIT];

	if(iCode == 0)
		bContinue = ReadData();
	else
	{
		m_ccContext.Reset(TRUE, SO_RECEIVE, iCode);
		bContinue = FALSE;
	}

	return bContinue;
}

BOOL CTcpClient::HandleWrite(WSANETWORKEVENTS& events)
{
	BOOL bContinue	= TRUE;
	int iCode		= events.iErrorCode[FD_WRITE_BIT];

	if(iCode == 0)
		bContinue = SendData();
	else
	{
		m_ccContext.Reset(TRUE, SO_SEND, iCode);
		bContinue = FALSE;
	}

	return bContinue;
}

BOOL CTcpClient::HandleConnect(WSANETWORKEVENTS& events)
{
	int iCode = events.iErrorCode[FD_CONNECT_BIT];

	if(iCode != 0)
	{
		m_ccContext.Reset(TRUE, SO_CONNECT, iCode);
		return FALSE;
	}

	if(::WSAEventSelect(m_soClient, m_evSocket, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		m_ccContext.Reset(TRUE, SO_CONNECT, ::WSAGetLastError());
		return FALSE;
	}

	SetConnected();

	if(TRIGGER(FireConnect()) == HR_ERROR)
	{
		m_ccContext.Reset(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpClient::HandleClose(WSANETWORKEVENTS& events)
{
	int iCode = events.iErrorCode[FD_CLOSE_BIT];

	if(iCode == 0)
		m_ccContext.Reset(TRUE, SO_CLOSE, SE_OK);
	else
		m_ccContext.Reset(TRUE, SO_CLOSE, iCode);

	return FALSE;
}

BOOL CTcpClient::ReadData()
{
	while(TRUE)
	{
		if(m_bPaused)
			break;

		int rc = recv(m_soClient, (char*)(BYTE*)m_rcBuffer, m_dwSocketBufferSize, 0);

		if(rc > 0)
		{
			if(TRIGGER(FireReceive(m_rcBuffer, rc)) == HR_ERROR)
			{
				TRACE("<C-CNNID: %Iu> OnReceive() event return 'HR_ERROR', connection will be closed !\n", m_dwConnID);
				m_ccContext.Reset(TRUE, SO_RECEIVE, ENSURE_ERROR_CANCELLED);

				return FALSE;
			}
		}
		else if(rc == SOCKET_ERROR)
		{
			int code = ::WSAGetLastError();

			if(code == WSAEWOULDBLOCK)
				break;
			else
			{
				m_ccContext.Reset(TRUE, SO_RECEIVE, code);
				return FALSE;
			}
		}
		else if(rc == 0)
		{
			m_ccContext.Reset(TRUE, SO_CLOSE, SE_OK);
			return FALSE;
		}
		else
			ASSERT(FALSE);
	}

	return TRUE;
}

BOOL CTcpClient::PauseReceive(BOOL bPause)
{
	if(!IsConnected())
	{
		::SetLastError(ERROR_INVALID_STATE);
		return FALSE;
	}

	if(m_bPaused == bPause)
		return TRUE;

	if(::WSAEventSelect(m_soClient, m_evSocket, bPause ? 0 : FD_READ | FD_WRITE | FD_CLOSE) != SOCKET_ERROR)
	{
		m_bPaused = bPause;

		if(!bPause)
			m_evUnpause.Set();

		return TRUE;
	}
	
	return FALSE;
}

BOOL CTcpClient::SendData()
{
	BOOL bBlocked = FALSE;

	while(TRUE)
	{
		TItemPtr itPtr(m_itPool, GetSendBuffer());

		if(!itPtr.IsValid())
			break;

		ASSERT(!itPtr->IsEmpty());

		if(!DoSendData(itPtr, bBlocked))
			return FALSE;

		if(bBlocked)
		{
			ASSERT(!itPtr->IsEmpty());

			CCriSecLock locallock(m_csSend);
			m_lsSend.PushFront(itPtr.Detach());

			break;
		}
	}

	return TRUE;
}

TItem* CTcpClient::GetSendBuffer()
{
	TItem* pItem = nullptr;

	if(m_iPending > 0)
	{
		CCriSecLock locallock(m_csSend);
		pItem = m_lsSend.PopFront();
	}

	return pItem;
}

BOOL CTcpClient::DoSendData(TItem* pItem, BOOL& bBlocked)
{
	while(!pItem->IsEmpty())
	{
		int rc = send(m_soClient, (char*)pItem->Ptr(), min(pItem->Size(), (int)m_dwSocketBufferSize), 0);

		if(rc > 0)
		{
			{
				CCriSecLock locallock(m_csSend);
				m_iPending -= rc;
			}

			if(TRIGGER(FireSend(pItem->Ptr(), rc)) == HR_ERROR)
			{
				TRACE("<C-CNNID: %Iu> OnSend() event should not return 'HR_ERROR' !!\n", m_dwConnID);
				ASSERT(FALSE);
			}

			pItem->Reduce(rc);
		}
		else if(rc == SOCKET_ERROR)
		{
			int code = ::WSAGetLastError();

			if(code == WSAEWOULDBLOCK)
			{
				bBlocked = TRUE;
				break;
			}
			else
			{
				m_ccContext.Reset(TRUE, SO_SEND, code);
				return FALSE;
			}
		}
		else
			ASSERT(FALSE);
	}

	return TRUE;
}

BOOL CTcpClient::Stop()
{
	DWORD dwCurrentThreadID = SELF_THREAD_ID;

	if(!CheckStoping(dwCurrentThreadID))
		return FALSE;

	WaitForWorkerThreadEnd(dwCurrentThreadID);

	SetConnected(FALSE);

	if(m_ccContext.bFireOnClose)
		FireClose(m_ccContext.enOperation, m_ccContext.iErrorCode);

	if(m_evSocket != nullptr)
	{
		::WSACloseEvent(m_evSocket);
		m_evSocket = nullptr;
	}

	if(m_soClient != INVALID_SOCKET)
	{
		shutdown(m_soClient, SD_SEND);
		closesocket(m_soClient);
		m_soClient = INVALID_SOCKET;
	}

	Reset();

	return TRUE;
}

void CTcpClient::Reset()
{
	CCriSecLock locallock(m_csSend);

	m_rcBuffer.Free();
	m_evBuffer.Reset();
	m_evWorker.Reset();
	m_evUnpause.Reset();
	m_lsSend.Clear();
	m_itPool.Clear();

	m_strHost.Empty();

	m_usPort	= 0;
	m_iPending	= 0;
	m_bPaused	= FALSE;
	m_enState	= SS_STOPPED;

	m_evWait.Set();
}

void CTcpClient::WaitForWorkerThreadEnd(DWORD dwCurrentThreadID)
{
	if(m_hWorker != nullptr)
	{
		if(dwCurrentThreadID != m_dwWorkerID)
		{
			m_evWorker.Set();
			ENSURE(::MsgWaitForSingleObject(m_hWorker));
		}

		::CloseHandle(m_hWorker);

		m_hWorker		= nullptr;
		m_dwWorkerID	= 0;
	}
}

BOOL CTcpClient::Send(const BYTE* pBuffer, int iLength, int iOffset)
{
	ASSERT(pBuffer && iLength > 0);

	if(iOffset != 0) pBuffer += iOffset;

	WSABUF buffer;
	buffer.len = iLength;
	buffer.buf = (char*)pBuffer;

	return SendPackets(&buffer, 1);
}

BOOL CTcpClient::DoSendPackets(const WSABUF pBuffers[], int iCount)
{
	ASSERT(pBuffers && iCount > 0);

	int result = NO_ERROR;

	if(pBuffers && iCount > 0)
	{
		if(IsConnected())
		{
			CCriSecLock locallock(m_csSend);

			if(IsConnected())
				result = SendInternal(pBuffers, iCount);
			else
				result = ERROR_INVALID_STATE;
		}
		else
			result = ERROR_INVALID_STATE;
	}
	else
		result = ERROR_INVALID_PARAMETER;

	if(result != NO_ERROR)
		::SetLastError(result);

	return (result == NO_ERROR);
}

int CTcpClient::SendInternal(const WSABUF pBuffers[], int iCount)
{
	ASSERT(m_iPending >= 0);

	int iPending = m_iPending;

	for(int i = 0; i < iCount; i++)
	{
		int iBufLen = pBuffers[i].len;

		if(iBufLen > 0)
		{
			BYTE* pBuffer = (BYTE*)pBuffers[i].buf;
			ASSERT(pBuffer);

			m_lsSend.Cat(pBuffer, iBufLen);
			m_iPending += iBufLen;

			ASSERT(m_iPending > 0);
		}
	}

	if(iPending == 0 && m_iPending > 0) m_evBuffer.Set();

	return NO_ERROR;
}

BOOL CTcpClient::SendSmallFile(LPCTSTR lpszFileName, const LPWSABUF pHead, const LPWSABUF pTail)
{
	CAtlFile file;
	CAtlFileMapping<> fmap;
	WSABUF szBuf[3];

	HRESULT hr = ::MakeSmallFilePackage(lpszFileName, file, fmap, szBuf, pHead, pTail);

	if(FAILED(hr))
	{
		::SetLastError(HRESULT_CODE(hr));
		return FALSE;
	}

	return SendPackets(szBuf, 3);
}

void CTcpClient::SetLastError(EnSocketError code, LPCSTR func, int ec)
{
	TRACE("%s --> Error: %d, EC: %d\n", func, code, ec);

	m_enLastError = code;
	::SetLastError(ec);
}

BOOL CTcpClient::GetLocalAddress(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)
{
	ASSERT(lpszAddress != nullptr && iAddressLen > 0);

	return ::GetSocketLocalAddress(m_soClient, lpszAddress, iAddressLen, usPort);
}

void CTcpClient::SetRemoteHost(LPCTSTR lpszHost, USHORT usPort)
{
	m_strHost = lpszHost;
	m_usPort  = usPort;
}

BOOL CTcpClient::GetRemoteHost(TCHAR lpszHost[], int& iHostLen, USHORT& usPort)
{
	BOOL isOK = FALSE;

	if(m_strHost.IsEmpty())
		return isOK;

	int iLen = m_strHost.GetLength() + 1;

	if(iHostLen >= iLen)
	{
		memcpy(lpszHost, CA2CT(m_strHost), iLen * sizeof(TCHAR));
		usPort = m_usPort;

		isOK = TRUE;
	}

	iHostLen = iLen;

	return isOK;
}

BOOL CTcpClient::GetRemoteHost(LPCSTR* lpszHost, USHORT* pusPort)
{
	*lpszHost = m_strHost;

	if(pusPort != nullptr)
		*pusPort = m_usPort;

	return !m_strHost.IsEmpty();
}


/* ========================================================================== */
/*  Common/debug/win32_crtdbg.cpp -- the leak-tracking global            */
/*  Active only when _DEBUG and _DETECT_MEMORY_LEAK are both defined.    */
/* ========================================================================== */

/* [amalgamated] #include "stdafx.h" */
/* [amalgamated] #include "win32_crtdbg.h" */

#if defined _DEBUG && defined _DETECT_MEMORY_LEAK

__dbg_impl::CDebugEnv __dbgEnv;

#endif // _DEBUG && defined _DETECT_MEMORY_LEAK


/* ========================================================================== */
/*  Link requirements (MSVC picks these up automatically)                  */
/* ========================================================================== */
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Winmm")
