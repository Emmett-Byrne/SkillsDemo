using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.AI;

public class PlayerController : MonoBehaviour
{
    public EnemyController enemyController;

    private BehaviourSelector behaviour = new BehaviourSelector();
    NavMeshAgent navAgent;

    void Start()
    {
        navAgent = GetComponent<NavMeshAgent>();
        BehaviourAction actionBehaviour = new BehaviourAction();
        actionBehaviour.setAction((senses) =>
        {
            Action action = new Action();
            action.Destination = senses.position + (senses.position - senses.nearestEnemy).normalized;
            action.Name = "retreat";

            return action;
        });

        actionBehaviour.setWeight((senses) =>
        {
            float temp = (senses.nearestEnemy - senses.position).magnitude;

            return temp;
        });

        behaviour.addBehaviour(actionBehaviour);
    }

    void Update()
    {
        Senses senses = new Senses();
        List<GameObject> enemies = enemyController.GetEnemies();
        List<Vector3> positions = new List<Vector3>();
        senses.countNearbyEnemies = enemies.Count();
        for (int i = 0; i < enemies.Count; i++)
        {
            positions.Add(enemies[i].transform.position);
        }
        senses.nearestEnemy = closestTo(positions);
        senses.position = transform.position;

        Debug.Log(behaviour.getAction(senses).Destination);
        navAgent.SetDestination(behaviour.getAction(senses).Destination);
    }

    Vector3 closestTo(List<Vector3> positions)
    {
        Vector3 closestPosition = Vector3.zero;
        float shortestDistance = float.MaxValue;

        for (int i = 0; i < positions.Count; i++)
        {
            Vector3 pos = positions[i] - transform.position;
            if (pos.magnitude < shortestDistance)
            {
                closestPosition = positions[i];
                shortestDistance = pos.magnitude;
            }
        }

        return closestPosition;
    }
}
