// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include <Engine.h>

AMyGameMode::AMyGameMode() 
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Logtemp临时日志记录类别名称，Warning日志记录级别，TEXT是打印的内容
	//日志记录级别常用的有三种,一种是Error、一种是Warning、一种Display,他们的级别是Error>warning>display
	//每一个颜色也是不一样的error是红色，Warning是黄色，Display是白色
	UE_LOG(LogTemp, Error, TEXT("My Name1 is ok"));
	UE_LOG(LogTemp, Warning, TEXT("My Name2 is ok"));
	UE_LOG(LogTemp, Display, TEXT("My Name3 is ok"));

	//打印到屏幕上
	//-1是默认值，5.0是打印显示的时间，FColor::Red显示的颜色，TEXT（打印的文本内容）
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("My Name is ok in screen"));


	//创建一个Fstring
	FString MyString = TEXT("I am string");
	//Fstring转化成FName
	FName MyName = FName(*MyString);
	//Fstring转化成FText
	FText MyText = FText::FromString(MyString);

	//FName转化成FString
	MyString = MyName.ToString();
	//Fname转化成FText
	FText text1 = FText::FromName(MyName);
	//Ftext转化成FString
	FString strFromText = text1.ToString();
	//注意这里FTEXT不能直接转化成FName需要转化成FString，然后在转化成FName}



	//// TArray
	//增
	MyArray.Add(10);//将元素添加到我们的数组中
	MyArray.Add(20);
	MyArray.Add(30);
	MyArray.AddUnique(20);//数组中不存在的元素才会添加到我们的数组中所有20就不会添加到数组中
	MyArray.AddUnique(40);//40数组中没有就可以添加到数组中
	PrintF();
	//删
	MyArray.Remove(20);//移除数组中所有的等值元素
	MyArray.RemoveAt(0);//移除数组中索引值为0的元素
	MyArray.RemoveSingle(10);//移除首个匹配的元素
	MyArray.Empty();//清空我们的元素
	MyArray.Reset();//重置我们的元素所有变为0
	
	//改
	MyArray.Insert(60,0);//这个是在我们的0号位置插入一个元素60
	int32& temp = MyArray[0];
	temp = 50;//这样就修改了我们的数组元素
	//查
	MyArray.Contains(10);//查找我们数组是否包含了某个元素
	MyArray.Find(10);//正向查找我们的第一个匹配的元素如果找到的话返回真否则为假
	MyArray.FindLast(10);//反向的查找我们的第一个匹配的元素找到为真否则为假


	//// TMap
	//增
	MyMap.Emplace(0,1);//用法和Add一样，都是往容器中添加元素
	MyMap.Emplace(1,2);
	MyMap.Emplace(2,3);
	PrintMap();

	//删
	MyMap.Remove(0);//移除key值为0的元素
	MyMap.Empty();//清空我们的数据

	//查找
	MyMap.Contains(1);//查找匹配的Key值是否存在找到返回真，否则为假，进行两次查找
	int32* isFind = MyMap.Find(6);//也是查找匹配的Key值是否存在找到为真否则为假，只进行一次查找返回的是指针
	const int32* isFind2 = MyMap.FindKey(2);//反向查找，通过查找Value的值查找Key返回的也是指针
	//分别获取Keys和Values
	TArray<int32> TestKeys;
	TArray<int32> TestValues;
	MyMap.GenerateKeyArray(TestKeys);
	MyMap.GenerateValueArray(TestValues);



	//// TSet
	//添加元素
	MySet.Add(TEXT("Banana"));
	MySet.Add(TEXT("Grapefruit"));
	MySet.Add(TEXT("Pineapple"));
	MySet.Emplace(TEXT("Orange"));//add和Emplace都是添加元素到容器中，但是Emplace可以避免在插入集合时创建的临时文件
	PrintSet();

	//合并元素
	TSet<FString>MySet2;
	MySet2.Add(TEXT("zhangsan"));
	MySet2.Add(TEXT("lisi"));
	MySet2.Add(TEXT("wangwu"));
	MySet.Append(MySet2);//Append将Myset2合并到Myset中
	PrintSet();

	//移除元素
	MySet.Remove(TEXT("Banana"));//remove函数会返回已删除元素的数量，如果给定的键未包含在集合中，则返回0
	MySet.Reset();//清空集合元素但是会保留内存
	MySet.Empty();//清空容器释放内存

	//查找元素
	int32 Count = MySet.Num();//num函数是查询集合中保存的元素数量
	bool isFind1 = MySet.Contains(TEXT("Banana"));//Contains函数是查询是否包含特定的元素，找到为真否则为假
	
	FString* isFind211 = MySet.Find(TEXT("Banan"));//Find返回指向元素数值的指针，如果映射不包含该键，则返回Null

	//Array函数
	TArray<FString> FruitArray = MySet.Array();//函数会返回一个Tarray,其中填充了TSet中每一个元素的副本

	//排序
	TSet<FString>TestSet = {TEXT("a"),TEXT("aa") ,TEXT("aaa"),TEXT("aaaa") };
	TestSet.Sort([](FString A, FString B) {return A.Len() > B.Len(); });

	//运算符 =
	TSet<FString>NewSet;
	NewSet = MySet;//讲MySet的里面的值赋给NewSet
	NewSet.Add("TEXT(OneOne)");

	//[]
	FSetElementId Index = NewSet.Add(TEXT("Twotwo"));//根据FSetElementID访问集合对应元素的引用
	TestSet[Index] = TEXT("One");

	//ReServe
	TSet<FString>NewSet1;
	NewSet1.Reserve(10);//预先分配内存，若输入的Number大于元素的个数，则会产生闲置内存（Slack）
	//Shrink
	for (int32 i = 0; i < 10; i++)
	{
		NewSet1.Add(FString::Printf(TEXT("NewSet%d"),i));//添加元素
	}
	for (int32  i = 0; i < 10; i+=2)
	{
		NewSet1.Remove(FSetElementId::FromInteger(i));//删除元素产生闲置内存
	}
	NewSet1.Shrink();//删除末端的空元素

	//Compact将容器中的所有空白的元素集合到一起放到末尾一起删除
	NewSet1.Compact();//注意Compact可能会改变元素之间的顺序，如果不想改变顺序，可以使用CompactStable
	NewSet1.Shrink();




	//基础数据类型的输出打印
	int32 MyInt = 10;
	float MyFloat = 5.0f;
	bool MyBool = true;
	char MyChar = 'A';
	FString MyString1 = TEXT("MyString1");
	FVector MyVector = FVector(0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("%d"), MyInt);
	UE_LOG(LogTemp, Warning, TEXT("%f"), MyFloat);
	UE_LOG(LogTemp, Warning, TEXT("%d"), MyBool);
	UE_LOG(LogTemp, Warning, TEXT("%c"), MyChar);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString1);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyVector.ToString());
}

void AMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}



void AMyGameMode::PrintF()
{	
	//我们用迭代器遍历一下数组打印出来
	/*for (auto It = MyArray.CreateConstIterator(); It; It++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), *It);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), *It));
	}*/

	for (auto it : MyArray) {
		UE_LOG(LogTemp, Warning, TEXT("%d"), it);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), it));
	}
}



void AMyGameMode::PrintMap()
{
	for (auto& TestMap : MyMap)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Key: %d" "Value: %d"), TestMap.Key, TestMap.Value));
		UE_LOG(LogTemp, Warning, TEXT("Key: %d Value: %d"), TestMap.Key, TestMap.Value);
	}
}


void AMyGameMode::PrintSet()
{
	for (auto& TestSet : MySet)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *TestSet));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TestSet);
	}
}


