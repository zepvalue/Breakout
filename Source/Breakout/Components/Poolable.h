#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include "StaticFunctions.h"
#include "Pooleable.generated.h"
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPooleable : public UInterface
{
	GENERATED_BODY()
};
/**
 *
 */
class PROJECTBREAKOUT_API IPooleable
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Is this pooleable object available */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pool)
	bool IsActive();
	/** Activate the pooleable object */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pool)
	void Activate();
	/** Deactivate the pooleable object */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pool)
	void Deactivate();
};
USTRUCT(BlueprintType)
struct PROJECTBREAKOUT_API FPoolDefinition
{
	GENERATED_BODY()
	// Variables
	// ---------------------------------------------------------------------------
public:
	/** Pool ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
	FName PoolID;
	/** Template class for this pool */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
	TSubclassOf<class AActor> TemplateClass;
	/** Initial size of the pool */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
	int StartPoolSize;
	/** Allow this pool to grow if more items are needed in runtime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
	bool bAllowToGrow;
	/** Allow this pool to grow if more items are needed in runtime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
	bool bHideInOutliner;
private:
	/** World context */
	UPROPERTY()
	UWorld* Context;
	/** Internal pool array */
	UPROPERTY()
	TArray<class AActor*> Pool;
	/** Pool tag on actors */
	/** Spawn parameters */
	FActorSpawnParameters SpawnParameters;
	static const FName PoolTag;
	/** Spawn location */
	static const FVector SpawnLocation;
	/** Spawn rotation */
	static const FRotator SpawnRotation;
	/** Is this template object member of the IPooleable interface */
	bool bIsPooleable;
	// Methods
	// ---------------------------------------------------------------------------
public:
	FORCEINLINE FPoolDefinition()
	{
		StartPoolSize = 5;
		bIsPooleable = false;
		bAllowToGrow = true;
	}
	/** Generate this object pool initial objects */
	FORCEINLINE void GeneratePool(class UWorld* World)
	{
		Context = World;
		bIsPooleable = TemplateClass.Get()->ImplementsInterface(UPooleable::StaticClass());
		SpawnParameters = FActorSpawnParameters();
#if WITH_EDITOR
		SpawnParameters.bHideFromSceneOutliner = bHideInOutliner;
#endif
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		IncrementPool(StartPoolSize);
	}
	/** Get an available pool object */
	FORCEINLINE AActor* GetPoolObject()
	{
		if (TemplateClass == nullptr) return nullptr;
		if (bIsPooleable)
		{
			for (int i = Pool.Num(); --i >= 0;)
			{
				if (!IsValid(Pool[i]))
				{
					Pool.RemoveAt(i);
					continue;
				}
				if (!IPooleable::Execute_IsActive(Pool[i]))
					return Pool[i];
			}
		}
		else
		{
			for (int i = Pool.Num(); --i >= 0;)
			{
				if (!IsValid(Pool[i]))
				{
					Pool.RemoveAt(i);
					continue;
				}
				if (Pool[i]->IsHidden())
					return Pool[i];
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("not available pool Size: %d"), Pool.Num());
		if (bAllowToGrow)
			return IncrementPool(5);
		UE_LOG(LogTemp, Warning, TEXT("Pool size exceeded: %s"), *PoolID.ToString());
		return nullptr;
	}
	FORCEINLINE float GetPoolSize()
	{
		return Pool.Num();
	}
	/** setup the == operator */
	FORCEINLINE bool operator==(const FPoolDefinition& Other) const
	{
		return PoolID == Other.PoolID;
	}
	/** Returns if an actor was pooled */
	FORCEINLINE static bool IsPooled(AActor* Actor)
	{
		return Actor->ActorHasTag(PoolTag);
	}
private:
	/** Increment the pool object */
	FORCEINLINE AActor* IncrementPool(int Size)
	{
		Pool.Reserve(Pool.Num() + Size);
		for (int i = 0; i < Size; i++)
		{
			AActor* Object = Context->SpawnActor<AActor>(TemplateClass.Get(), SpawnLocation, SpawnRotation, SpawnParameters);
			if (Object != nullptr)
			{
#if WITH_EDITOR
				Object->SetActorLabel(FString::Printf(TEXT("%s_Pool%d"), *TemplateClass.Get()->GetName(), Pool.Num()), false);
#endif
				Object->Tags.Add(PoolTag);
				if (bIsPooleable)
				{
					IPooleable::Execute_Deactivate(Object);
				}
				else
				{
					UStaticFunctions::SetActorActive(Object, false, true);
				}
				Pool.Emplace(Object);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not create pool object for %s"), *PoolID.ToString());
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Pool Size: %d"), Pool.Num());
		return Pool[Pool.Num() - Size];
	}
};