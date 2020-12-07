#include "Firearm.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFirearm::AFirearm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Root = RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AFirearm::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirearm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
