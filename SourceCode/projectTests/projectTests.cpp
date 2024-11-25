#include "pch.h"
#include "CppUnitTest.h"
#include "../project/mapping.c"
#include "../project/truck.c"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace projectTests
{
	TEST_CLASS(MappingTest)
	{
		TEST_METHOD(TestDistance_T001)
		{
			struct Point p1 = { 0, 0 };
			struct Point p2 = { 3, 4 };

			double expectedDistance = 5.0;
			double calculatedDistance = distance(&p1, &p2);

			Assert::AreEqual(expectedDistance, calculatedDistance, 0.001);
		}
		TEST_METHOD(TestBlueRouteCreation_T002)
		{
			struct Route blueRoute = getBlueRoute();

			Assert::IsTrue(blueRoute.numPoints > 0);

			Assert::AreEqual(BLUE, blueRoute.routeSymbol);

		}
		TEST_METHOD(TestGreenRouteCreation_T003)
		{
			struct Route greenRoute = getGreenRoute();
			Assert::IsTrue(greenRoute.numPoints > 0);
			Assert::AreEqual(GREEN, greenRoute.routeSymbol);
		}
		TEST_METHOD(TestYellowRouteCreation_T004)
		{
			struct Route yellowRoute = getYellowRoute();
			Assert::IsTrue(yellowRoute.numPoints > 0);
			Assert::AreEqual(YELLOW, yellowRoute.routeSymbol);
		}
		TEST_METHOD(TestShortestPathSamePoint_T005)
		{

			struct Map map = populateMap();
			struct Point start = { 3, 3 };
			struct Point dest = start;

			struct Route result = shortestPath(&map, start, dest);

			Assert::AreEqual(1, result.numPoints);
		}
		TEST_METHOD(TestShortestPathWithBuilding_T006)
		{

			struct Map map = populateMap();
			struct Point start = { 1, 0 };
			struct Point dest = { 1, 2 };


			struct Route result = shortestPath(&map, start, dest);


			Assert::AreEqual(2, result.numPoints);
		}

		TEST_METHOD(TestShortestPathAroundBuilding_T007)
		{

			struct Map map = populateMap();
			struct Point start = { 3, 0 };
			struct Point dest = { 3, 2 };

			struct Route result = shortestPath(&map, start, dest);

			Assert::IsTrue(result.numPoints > 0);

			Assert::AreEqual((char)3, result.points[0].row);
			Assert::AreEqual((char)1, result.points[0].col);
		}
		TEST_METHOD(TestAddRoute_T008)
		{
			struct Map originalMap = populateMap();
			struct Route blueRoute = getBlueRoute();

			struct Map updatedMap = addRoute(&originalMap, &blueRoute);

			for (int i = 0; i < blueRoute.numPoints; i++)
			{
				int row = blueRoute.points[i].row;
				int col = blueRoute.points[i].col;
				Assert::IsTrue(updatedMap.squares[row][col]);
			}
		}
		TEST_METHOD(TestPointEqual_T009)
		{
			struct Point p1 = { 5, 5 };
			struct Point p2 = { 5, 5 };

			Assert::IsTrue(eqPt(p1, p2));

		}
		TEST_METHOD(TestPointUnequal_T010)
		{
			struct Point p1 = { 5, 5 };
			struct Point p2 = { 6, 6 };
			Assert::IsFalse(eqPt(p1, p2));
		}
		TEST_METHOD(TestGetClosestPoint_T011)
		{
			struct Route route;
			route.points[0] = { 0, 0 };
			route.points[1] = { 5, 5 };
			route.points[2] = { 10, 10 };
			route.numPoints = 3;

			struct Point testPoint = { 4, 4 };

			int closestIndex = getClosestPoint(&route, testPoint);

			Assert::AreEqual(1, closestIndex);
		}
		TEST_METHOD(TestAddPointRoute_T012)
		{
			struct Route route = { 0 };
			struct Point pt1 = { 5, 5 };
			struct Point pt2 = { 6, 6 };

			addPtToRoute(&route, pt1);
			Assert::AreEqual(1, route.numPoints);

			addPtToRoute(&route, pt2);
			Assert::AreEqual(2, route.numPoints);

			Assert::AreEqual(pt1.row, route.points[0].row);
			Assert::AreEqual(pt1.col, route.points[0].col);

			Assert::AreEqual(pt2.row, route.points[1].row);
			Assert::AreEqual(pt2.col, route.points[1].col);
		}
		TEST_METHOD(TestGetPossibleMoves_T013)
		{
			struct Map map = populateMap();
			struct Point p1 = { 10, 10 };
			struct Point p2 = { 9, 10 };

			struct Route possibleMoves = getPossibleMoves(&map, p1, p2);

			Assert::IsTrue(possibleMoves.numPoints > 0);
			Assert::IsTrue(possibleMoves.numPoints <= 8);
		}
	};
	
	TEST_CLASS(PackageValidationTests)
	{
	public:
		
		TEST_METHOD(TestValidPackage_T014)
		{
			Assert::AreEqual(1, isPackageValid(10.0, 1.0));
		}

		TEST_METHOD(TestInvalidPackage_T015)
		{
			Assert::AreEqual(0, isPackageValid(-1.0, 1.0));
			Assert::AreEqual(0, isPackageValid(1.0, -1.0));
			Assert::AreEqual(0, isPackageValid(0.0, 1.0));
			Assert::AreEqual(0, isPackageValid(1.0, 0.0));
		}

	};
}
