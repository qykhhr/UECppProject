// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UENUM(BlueprintType)
namespace MyEnumType22
{
	enum MyCustomEnum
	{
		Type1,
		Type2,
		Type3,
	};
}

UENUM(BlueprintType)
enum class EMyTestEnum : uint8
{
	OneType UMETA(DisplayName = "OneType"),
	TwoeType UMETA(DisplayName = "TwoeType"),
	ThreeType UMETA(DisplayName = "ThreeType")
};

USTRUCT(BlueprintType)
struct FMyTestStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestStruct")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestStruct2")
	FString MyName;

};

UCLASS()
class UECPPPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//仅在类默认设置可见
	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultsOnlyint;
	//仅在实例化细节面板可见
	UPROPERTY(VisibleInstanceOnly)
	FVector VisibleInstanceOnlyVector;
	//类默认设置和实例化细节面板都可见
	UPROPERTY(VisibleAnywhere)
	FString VisibleAnywhereString;

	//仅在类默认设置里可编辑
	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt;
	//仅在实例化细节面板可编辑
	UPROPERTY(EditInstanceOnly)
	FVector EditInstancesOnlyVector;
	//在类默认设置和实例化细节面板都可以编辑
	UPROPERTY(EditAnywhere)
	FString EditAnywhereString;


	//仅仅蓝图可读
	UPROPERTY(BlueprintReadOnly)
	int32 BlueprintReadOnlyInt;
	//蓝图可读可写
	UPROPERTY(BlueprintReadWrite)
	int32 BlueprintReadWriteint;

	//Category目录
	//第一层目录
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopCategory")
		int32 value1;
	//第二层目录
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopCategory|SubCategory")
		int32 value2;
	//别名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Vlaue3DisplayName"))
	int32 Myvalue3;
	//EditCondition条件控制编辑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Controller"))
	bool isController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isController"))
	float value3;

	//解释变量说明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "isControllerTrue"))
		float isTrue;




	//暴露我们的函数在蓝图中调用
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
		void PrintF1();

	//纯虚函数的定义BlueprintPure
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyFunction")
		bool PrintF2();


	//BlueprintImplementableEvent在C++中声明，不能定义，蓝图可重载，没返回值的是事件，有返回值的是函数
	UFUNCTION(BlueprintImplementableEvent)
		void Test1();
	UFUNCTION(BlueprintImplementableEvent)
		int Test2();
	UFUNCTION(BlueprintImplementableEvent)
		void Test11(const FString& str);
	UFUNCTION(BlueprintImplementableEvent)
		int Test22(const FString& str);

	/*
	BlueprintNativeEvent在C++中声明和实现，蓝图可重载或者不重载	
	C++中实现的方法需要增加"_Implementation",如：TestA需要变成TestA_Implementation
	蓝图中实现了方法后，会先调用蓝图中连接的节点（重载），然后再执行实现的TestAA_Implementation方法
	* */
	UFUNCTION(BlueprintNativeEvent)
	void TestAB();
	UFUNCTION(BlueprintNativeEvent)
	int TestB();
	UFUNCTION(BlueprintNativeEvent)
	void TestC(const FString& str);
	UFUNCTION(BlueprintNativeEvent)
	int TestD(const FString& str);

	UFUNCTION(BlueprintCallable, Category = "MyFunction", meta = (DisplayName = "MyPrinttest"))
	void PrintTest();


	//定义枚举
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum")
	TEnumAsByte<MyEnumType22::MyCustomEnum> MyCustomEnum;

	//另一种枚举声明方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum")
	EMyTestEnum MyTestEnum;

	//定义结构体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCustomStruct")
	FMyTestStruct myCustomStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyExposeOnSpawn", meta = (ExposeOnSpawn = "ExposeOnSpawnValue"))
		float MyHealth;
};
