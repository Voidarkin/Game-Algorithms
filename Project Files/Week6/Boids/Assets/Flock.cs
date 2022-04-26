using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Flock : MonoBehaviour
{
    public List<Boid> boids;
    public float Speed;
    public float TurnSpeed;
    public float NeighborRadius;
    public float FOV;
    public float AvoidDistance;
    public GameObject target;
    private void Awake()
    {
        boids = new List<Boid>();
    }


    // Update is called once per frame
    void Update()
    {
        
    }

    internal void AddBoid(Boid boid)
    {
        boids.Add(boid);
        boid.SetFlock(this);
    }
}
