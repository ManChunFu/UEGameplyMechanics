// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSand.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

AQuickSand::AQuickSand()
{
	SurfaceComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SurfaceComp"));
	SurfaceComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SurfaceComp;

	MoveableComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoveableComp"));
	MoveableComp->SetupAttachment(SurfaceComp);
	MoveableComp->OnComponentBeginOverlap.AddDynamic(this, &AQuickSand::OverlapMoveableComp);
	MoveableComp->OnComponentEndOverlap.AddDynamic(this, &AQuickSand::EndOverlapMoveableComp);

	DeadZoneComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DeadZoneComp"));
	DeadZoneComp->SetupAttachment(SurfaceComp);
	DeadZoneComp->OnComponentBeginOverlap.AddDynamic(this, &AQuickSand::OverlapDeadZoneComp);

}

void AQuickSand::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = MoveableComp->GetRelativeLocation();

	DefaultFirstTimeDelay = FirstTimeDelay;
}

void AQuickSand::OverlapMoveableComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Something is on"));

	if (OtherActor != this)
	{
		OverlappingActors.Add(OtherActor);
	}
	GetWorldTimerManager().SetTimer(MoveCompTimerHandle, this, &AQuickSand::SinkDown, SinkingRate, true, FirstTimeDelay);
	Counter = 0;
}

void AQuickSand::EndOverlapMoveableComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this)
	{
		while (OverlappingActors.Num() > 0)
		{
			int Temp = OverlappingActors.Find(OverlappingActors.Last());
			OverlappingActors.RemoveAt(Temp);
		}
	}
	GetWorldTimerManager().SetTimer(MoveBackCompTimerHandle, this, &AQuickSand::SetBackToOriginalLocation, SinkingRate, true);
}

void AQuickSand::OverlapDeadZoneComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappingActors.Num() > 0)
	{
		while (OverlappingActors.Num() > 0)
		{
			OverlappingActors.Last()->Destroy();
		}
	}
}

void AQuickSand::SinkDown()
{
	FirstTimeDelay = 0.0f;

	if (OverlappingActors.Num() < 0)
	{
		GetWorldTimerManager().PauseTimer(MoveCompTimerHandle);
		return;
	}

	if (OverlappingActors.Num() > 0)
	{
		FVector Location = MoveableComp->GetRelativeLocation();
		FVector NewLocation = { Location.X, Location.Y, Location.Z - SinkingLength };
		MoveableComp->SetRelativeLocation(NewLocation);
		Counter++;
	}
}

void AQuickSand::SetBackToOriginalLocation()
{
	FVector CurrentLocation = MoveableComp->GetRelativeLocation();

	if (CurrentLocation.Z > OriginalLocation.Z || OverlappingActors.Num() > 0)
	{
		FirstTimeDelay = DefaultFirstTimeDelay;
		GetWorldTimerManager().PauseTimer(MoveBackCompTimerHandle);
		MoveableComp->SetRelativeLocation(OriginalLocation);

		return;
	}

	FVector NewLocation = { CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + SinkingLength };
	MoveableComp->SetRelativeLocation(NewLocation);
}


