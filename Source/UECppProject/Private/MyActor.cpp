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


	//碰撞设置
	//MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//MyBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//碰撞对象类型
	//MyBox->SetCollisionObjectType(ECC_WorldStatic);
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);
	//MyBox->SetCollisionObjectType(ECC_Pawn);
	//MyBox->SetCollisionObjectType(ECC_PhysicsBody);
	//MyBox->SetCollisionObjectType(ECC_Vehicle);
	//MyBox->SetCollisionObjectType(ECC_Destructible);

	//碰撞响应
	//MyBox->SetCollisionResponseToAllChannels(ECR_Block); //对所有的通道进行设置响应为Block，阻挡
	MyBox->SetCollisionResponseToAllChannels(ECR_Overlap); //对所有的通道进行设置响应为Overlap，重叠
	//MyBox->SetCollisionResponseToAllChannels(ECR_Ignore); //忽略
	//MyBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//对单个通道设置响应
	//MyBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);//
	//MyBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

	//设置Box大小
	MyBox->SetBoxExtent(FVector(64, 64, 64));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	//默认粒子不激活
	if (MyParticle) {
		MyParticle->Deactivate();
	}

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


	//动态绑定BeginOverlap和EndOverlap
	MyBox->OnComponentBeginOverlap.AddDynamic(this,&AMyActor::BeginOverlapFunction);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AMyActor::EndOverlapFunction);
	MyBox->OnComponentHit.AddDynamic(this, &AMyActor::HitFunction);
}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MyOffset = FVector(1, 0, 0);
	FHitResult HitResult; //碰撞信息
	//添加Actor的本地坐标偏移
	AddActorLocalOffset(MyOffset, false, &HitResult);

	//添加Actor的世界坐标偏移
	//AddActorWorldOffset(MyOffset, false, &HitResult);
}

void AMyActor::BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MyParticle) {
		MyParticle->Activate();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BeginOverlapEvent is success!"));
}

void AMyActor::EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MyParticle) {
		MyParticle->Deactivate();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EndOverlapEvent is success!"));
}

void AMyActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HitFunction is success!"));
}

