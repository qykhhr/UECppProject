// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//调用事件函数，启动后先调用TestAA事件，调用蓝图中连接的节点，然后再执行实现的TestAA_Implementation方法
	TestAB();

	TSubclassOf<UMyObject> MySubClassObject = UMyObject::StaticClass();
	MyTestObject = NewObject<UMyObject>(GetWorld(), MySubClassObject);
	if (MyTestObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyTestObject is %s"), *MyTestObject->GetName());
		UE_LOG(LogTemp, Warning, TEXT("MyTestObject Health is %f"), MyTestObject->MyDataTableStruct.Health);
		UE_LOG(LogTemp, Warning, TEXT("MyTestObject Name is %s"), *MyTestObject->MyDataTableStruct.Name);
		UE_LOG(LogTemp, Warning, TEXT("MyTestObject level is %f"), MyTestObject->MyDataTableStruct.level);
	}

	MyInstance = Cast<UMyGameInstance>(GetWorld()->GetFirstPlayerController()->GetGameInstance());
	if (MyInstance) {
		UE_LOG(LogTemp, Warning, TEXT("MyInstance is %s"), *MyInstance->GetName());
		UE_LOG(LogTemp, Warning, TEXT("MyInstance MyAppID is %s"), *MyInstance->MyAppID);
		UE_LOG(LogTemp, Warning, TEXT("MyInstance MyUserID is %s"), *MyInstance->MyUserID);
		UE_LOG(LogTemp, Warning, TEXT("MyInstance MyName is %s"), *MyInstance->MyName);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPawn::PrintF1()
{
}

bool AMyPawn::PrintF2()
{
	return true;
}

void AMyPawn::TestAB_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TestAA"));
}

int AMyPawn::TestB_Implementation()
{
	return 0;
}

void AMyPawn::TestC_Implementation(const FString& str)
{
}

int AMyPawn::TestD_Implementation(const FString& str)
{
	return 0;
}

void AMyPawn::PrintTest()
{
}
