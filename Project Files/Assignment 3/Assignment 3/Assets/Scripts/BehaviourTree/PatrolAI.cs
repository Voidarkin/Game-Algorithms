using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PatrolAI : BehaviorTree {
    public string WaypointName = "TargetWaypoint";
    public GameObject[] waypoints;
    public int index;
    public float Speed = 5.0f;
    public float TurnSpeed = 2.0f;
    public float Accuracy = 1.5f;
    public float SpinSpeed = 120.0f;
    
	//construct the actual tree
	void Start () {
        
        // create nodes
        Selector TreeRoot = new Selector();
        Sequence Patrol = new Sequence();
        MoveTo MoveToWP = new MoveTo();
        SelectNextGameObject PickNextWP = new SelectNextGameObject();
        waypoints = GameObject.FindGameObjectsWithTag(WaypointName);

        // create blackboard keys and initialize them with values
        // NOTE - SHOULD BE USING CONSTANTS

        Speed = Random.Range(1, 5);
        SetValue("Waypoints", waypoints);
        SetValue("CurrentWaypoint", waypoints[0]);
        SetValue("WaypointIndex", 0);
        SetValue("Speed", Speed);
        SetValue("TurnSpeed", TurnSpeed);
        SetValue("Accuracy", Accuracy);
        // set node parameters - connect them to the blackboard
        MoveToWP.TargetName = "CurrentWaypoint";
        PickNextWP.ArrayKey = "Waypoints";
        PickNextWP.GameObjectKey = "CurrentWaypoint";
        PickNextWP.IndexKey = "WaypointIndex";
        // connect nodes
        Patrol.children.Add(MoveToWP);
        Patrol.children.Add(PickNextWP);
        TreeRoot.children.Add(Patrol);
        Patrol.tree = this;
        TreeRoot.tree = this;
        MoveToWP.tree = this;
        PickNextWP.tree = this;
        root = TreeRoot;
        
	}

    // we don't need an update - the base class will deal with that.
    // but, since we have one, we can use it to set some of the moveto parameters on the fly
    // which lets us tweak them in the inspector
    public override void Update()
    {
        SetValue("Speed", Speed);
        SetValue("TurnSpeed", TurnSpeed);
        SetValue("Accuracy", Accuracy);
        base.Update();
    }
}
