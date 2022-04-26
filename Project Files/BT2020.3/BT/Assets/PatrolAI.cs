using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PatrolAI : BehaviorTree {
    public GameObject[] waypoints;
    public int index;
    public float Speed;
    public float TurnSpeed;
    public float Accuracy;
    public float SpinSpeed;
	//construct the actual tree
	void Start () {
        
        // create nodes
        Selector TreeRoot = new Selector();
        Sequence Patrol = new Sequence();
        MoveTo MoveToWP = new MoveTo();
        Wait Pause = new Wait();
        Spin Turn = new Spin();
        SelectNextGameObject PickNextWP = new SelectNextGameObject();
        // create blackboard keys and initialize them with values
        // NOTE - SHOULD BE USING CONSTANTS
        TurnSpeed = 2.0f;
        Speed = 5.0f;
        Accuracy = 1.5f;
        SpinSpeed = 120.0f;
        SetValue("Waypoints", waypoints);
        SetValue("CurrentWaypoint", waypoints[0]);
        SetValue("WaypointIndex", 0);
        SetValue("TimeToPause", 3.0f);
        SetValue("Speed", Speed);
        SetValue("TurnSpeed", TurnSpeed);
        SetValue("SpinSpeed", SpinSpeed);
        SetValue("Accuracy", Accuracy);
        // set node parameters - connect them to the blackboard
        MoveToWP.TargetName = "CurrentWaypoint";
        Pause.TimeToWaitKey = "TimeToPause";
        PickNextWP.ArrayKey = "Waypoints";
        PickNextWP.GameObjectKey = "CurrentWaypoint";
        PickNextWP.IndexKey = "WaypointIndex";
        Turn.SpinSpeedKey = "SpinSpeed";
        // connect nodes
        Patrol.children.Add(MoveToWP);
        Patrol.children.Add(Turn);
        Patrol.children.Add(Pause);
        Patrol.children.Add(Turn);
        Patrol.children.Add(PickNextWP);
        TreeRoot.children.Add(Patrol);
        Patrol.tree = this;
        TreeRoot.tree = this;
        MoveToWP.tree = this;
        Pause.tree = this;
        Turn.tree = this;
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
        SetValue("SpinSpeed", SpinSpeed);
        base.Update();
    }
}
