modded class DayZGame
{
    vector TeleportEntityToSafePosition(EntityAI entity, vector centerPos, float minRadius, float maxRadius, vector size, vector orientation)
    {
        array<vector> potentialPositions = RandomVectorArrayInRadius(20, minRadius, maxRadius, centerPos);

        array<vector> safePositions;
        SafeLandPos(potentialPositions, centerPos, size, orientation, safePositions);

        int randomIndex = Math.RandomInt(0, safePositions.Count());
        vector chosenPosition = safePositions[randomIndex];

        entity.SetPosition(chosenPosition);

        return chosenPosition;
    }

    array<vector> RandomVectorArrayInRadius(int loops, float minRadius, float maxRadius, vector centerPos)
    {
        private float RandomX;
        private float RandomZ;
        private vector pos;
        autoptr array<vector> m_RandomPosRay = new array<vector>;

        for (int i = 0; i < loops; i++)
        {
            float randomRadius = Math.RandomFloatInclusive(minRadius, maxRadius);
            RandomX = centerPos[0] + randomRadius * Math.Cos(Math.RandomFloatInclusive(0.01, 6.28));
            RandomZ = centerPos[2] + randomRadius * Math.Sin(Math.RandomFloatInclusive(0.01, 6.28));
            pos = Vector(RandomX, centerPos[1], RandomZ);
            m_RandomPosRay.Insert(pos);
        }
        return m_RandomPosRay;
    }

    void SafeLandPos(array<vector> PosVectorArray, vector DefaultPos, vector size, vector orientation, out array<vector> SafeLandPosArray)
    {						
        private string w_Surface;
        
        SafeLandPosArray = new array<vector>;
        
        array<Object> excluded_objects = new array<Object>;
        
        array<Object> nearby_objects = new array<Object>;
            
        for (int i = 0; i < PosVectorArray.Count(); ++i)
        {        
            GetGame().SurfaceGetType3D (PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[1], PosVectorArray.Get(i)[2], w_Surface); 

            // Adjust the Y-coordinate to match the terrain's elevation
            vector adjustedPosition = Vector(PosVectorArray.Get(i)[0], GetGame().SurfaceY(PosVectorArray.Get(i)[0],PosVectorArray.Get(i)[2]),PosVectorArray.Get(i)[2]);

            if (!GetGame().IsBoxColliding(adjustedPosition, orientation, size, excluded_objects, nearby_objects) && w_Surface != "FreshWater" && w_Surface != "sea" && !GetGame().SurfaceIsSea(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[2]))
            {
                SafeLandPosArray.Insert(adjustedPosition);  // Insert the adjusted position
            }
            
            delete excluded_objects;    
            delete nearby_objects;    
            w_Surface = "";
        }
        
        if (SafeLandPosArray.Count() == 0)
        {        
            SafeLandPosArray.Insert(DefaultPos);
        } 
    }
}