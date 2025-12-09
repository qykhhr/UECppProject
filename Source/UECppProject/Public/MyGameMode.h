// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MyGameState.h"
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "MyPawn.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UECPPPROJECT_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

	AMyGameMode();

public:
	//在游戏运行的一开始执行这个Beginplay()函数
	virtual void BeginPlay() override;
	//游戏运行的时候每一帧都在执行这个函数
	virtual void Tick(float DeltaTime) override;
	//这个是当我们游戏退出或者切换关卡的时候关卡卸载也会执行这个Endplay函数
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//变量类型测试

	//布尔类型变量声明
	bool varBool;
	//整型32位的变量声明
	int32 varInt32;
	//整型64位的变量声明
	int64 varInt64;
	//字节类型的变量声明
	BYTE varByte;
	//FString类型的变量声明字符串的类型
	FString varString;
	//FName名称类型的变量声明
	FName varName;
	//FText文本类型的变量声明
	FText varText;
	//FVector向量类型的变量声明
	FVector varVector;//这个就是X轴，Y轴，Z轴的坐标
	//FRotator旋转类型的变量声明
	FRotator varRotator;//这个就是X轴的旋转Roll,Y轴的旋转Pitch,Z轴的旋转Yaw
	//FTransform类型的变量声明
	FTransform varTransform;//这个就是既有FVector也有FRotator,还有缩放Scale三者的集合类型int
	

	//TArrayTArray 是虚幻C++中的动态数组TArray 特点 : 速度快，内存消耗小，安全性高。并且TArray 所有元素均完全为相同类型，不能进行不同元素类型的混合
	TArray<int32>MyArray;
	void PrintF();

	//TMap-是一种键值对容器，里面的数据都是成对出现的（Key，Value），Value通过Key值来获取，且Key值不能重复，key值唯一。
	TMap<int32, int32>MyMap;
	void PrintMap();

	//TSet- TSet是一种快速容器类，（通常）用于在排序不重要的情况下存储唯一元素。
	//TSet 类似于 TMap 和 TMultiMap，但有一个重要区别：TSet 是通过对元素求值的可覆盖函数，使用数据值本身作为键，而不是将数据值与独立的键相关联。
	//TSet 可以非常快速地添加、查找和删除元素（恒定时间）,-TSet 也是值类型，支持常规复制、赋值和析构函数操作，以及其元素较强的所有权。

	TSet<FString>MySet;
	void PrintSet();

};
