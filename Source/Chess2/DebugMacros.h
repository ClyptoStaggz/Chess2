#pragma once

#include "DrawDebugHelpers.h"


#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.0f, 15, FColor::Green, true);
#define DRAW_SPHERE_COLOR(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 8.0f, 15, Color, false, 5.f);
#define DRAW_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 30.0f, 15, FColor::Green, false, -1.f);
#define DRAW_LINE(Location, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, -1.0f, 0, 5.0f);
#define DRAW_LINE_SingleFrame(Location, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, false, -1.0f, 0, 5.0f);
#define DRAW_POINT(EndLocation) if(GetWorld()) DrawDebugPoint(GetWorld(), EndLocation, 20.0f, FColor::Blue, true);
#define DRAW_POINT_SingleFrame(EndLocation) if(GetWorld()) DrawDebugPoint(GetWorld(), EndLocation, 20.0f, FColor::Blue, false, -1.0f);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
{ \
	DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, -1.0f, 0, 5.0f); \
	DrawDebugPoint(GetWorld(), EndLocation, 10.0f, FColor::Blue, true); \
}
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if(GetWorld()) \
{ \
	DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, false, -1.0f, 0, 5.0f); \
	DrawDebugPoint(GetWorld(), EndLocation, 10.0f, FColor::Blue, false, -1.0f); \
}


/*
* Print String
*/

#define PRINT_STRING_BLUE(Message)if(GEngine && GetWorld()) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT(Message));
#define PRINT_STRING_RED(Message)if(GEngine && GetWorld()) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT(Message));