using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct Senses
{
    public int countNearbyEnemies { get; set; }
    public int currentHp { get; set; }
    public Vector3 nearestEnemy { get; set; }
    public Vector3 objective { get; set; }
    public Vector3 position { get; set; }
}

public struct Action
{
    public string Name { get; set; }
    public Vector3 Destination { get; set; }

    public Action(string name, Vector3 destination)
    {
        Name = name; //I could use an enum here
        Destination = destination;
    }
}

public interface Behaviour
{
    public float getWeight(Senses senses);
    public Action getAction(Senses senses);
}

public class BehaviourSelector : Behaviour
{
    private List<Behaviour> behaviours = new List<Behaviour>();

    public BehaviourSelector()
    {
        weightFunc = (_) => 0f;
    }

    private Func<Senses, float> weightFunc;

    public void addBehaviour(Behaviour behaviour)
    {
        behaviours.Add(behaviour);
    }

    public float getWeight(Senses senses)
    {
        return weightFunc(senses);
    }

    public Action getAction(Senses senses)
    {
        float bestWeight = 0f;
        Action action = new Action();
        foreach (var behaviour in behaviours)
        {
            float newWeight = behaviour.getWeight(senses);
            if (newWeight > bestWeight)
            {
                bestWeight = newWeight;
                action = behaviour.getAction(senses);
            }
        }
        return action;
    }
}

public class BehaviourAction : Behaviour
{
    private Func<Senses, Action> actionFunc;
    private Func<Senses, float> weightFunc;

    public BehaviourAction()
    {
        actionFunc = (_) => new Action("", new Vector3(0,0,0));
        weightFunc = (_) => 0f;
    }

    public void setAction(Func<Senses, Action> func)
    {
        actionFunc = func;
    }

    public void setWeight(Func<Senses, float> func)
    {
        weightFunc = func;
    }

    public float getWeight(Senses senses)
    {
        return weightFunc(senses);
    }
    public Action getAction(Senses senses)
    {
        return actionFunc(senses);
    }
}