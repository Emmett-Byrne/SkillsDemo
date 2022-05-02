using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    public List<GameObject> enemies;
    
    public List<GameObject> GetEnemies()
    {
        return enemies;
    }
}
