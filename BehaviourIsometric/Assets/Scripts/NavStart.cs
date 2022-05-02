using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavStart : MonoBehaviour
{
    public Transform destination;
    public Transform destination2;
    NavMeshAgent navAgent;

    void Start()
    {
        navAgent = this.GetComponent<NavMeshAgent>();
        if (destination)
        {
            Vector3 target = destination.transform.position;
            navAgent.SetDestination(target);
        }        
    }

    void Update()
    {
        if(Input.GetKeyDown("space"))
        {
            navAgent.SetDestination(destination2.transform.position);
        }

        if(Input.GetKeyDown("c"))
        {
            navAgent.SetDestination(transform.position);
        }
    }
}
