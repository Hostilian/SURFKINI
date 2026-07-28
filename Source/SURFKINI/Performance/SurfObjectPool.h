// SURFKINI — High-Performance C++ Object Pool Template
// Adapted from OpenPool/cpp-object-pool & UE Memory Pooling Guidelines.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

template <typename T>
class TSurfObjectPool
{
public:
	TSurfObjectPool(int32 InitialCapacity = 64)
	{
		Pool.Reserve(InitialCapacity);
	}

	~TSurfObjectPool()
	{
		Pool.Empty();
	}

	/** Acquires an object from the pool or allocates if empty */
	T* Acquire()
	{
		if (Pool.Num() > 0)
		{
			T* Item = Pool.Pop(false);
			return Item;
		}
		return new T();
	}

	/** Releases an object back to the pool */
	void Release(T* Item)
	{
		if (Item)
		{
			Pool.Push(Item);
		}
	}

	int32 GetAvailableCount() const
	{
		return Pool.Num();
	}

private:
	TArray<T*> Pool;
};
