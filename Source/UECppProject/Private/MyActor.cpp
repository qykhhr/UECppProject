// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomStaticMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticleSystem"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));

	RootComponent = MyScene;
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	//静态加载资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TempStaticMesh(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TempParticleSystem(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticleSystem.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave> TempSound(TEXT("SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSound.Object);

	//静态加载类
	static ConstructorHelpers::FClassFinder<AActor> TempMyActor(TEXT("Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	MyActor = TempMyActor.Class;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	if (MyActor) {
		UE_LOG(LogTemp, Warning, TEXT("MyActor is %s"), *MyActor->GetName());
	}
	
	//动态加载资源
	UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MyTempStaticMesh) {
		MyMesh->SetStaticMesh(MyTempStaticMesh);
	}

	//动态加载类资源
	UClass* MyTempClass = LoadClass<AActor>(this, TEXT("Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	if (MyTempClass)
	{
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(MyTempClass, FVector::ZeroVector, FRotator::ZeroRotator);

	}

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

