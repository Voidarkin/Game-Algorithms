using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TankAI : BehaviorTree {
    
    private GameObject Turret;

    public float TurnSpeed = 2.0f;
    public float SpinSpeed = 120.0f;
    
	//construct the actual tree
	void Start () {

        Turret = this.gameObject;

        // create nodes
        Selector TreeRoot = new Selector();
        Sequence TurretAI = new Sequence();
        Shooting Shot = new Shooting();
        Spin Turn = new Spin();
        //Wait ShotDelay = new Wait();
        
        //Parallel RotateShoot = new Parallel();
        //Sequence Firing = new Sequence();

        // create blackboard keys and initialize them with values
        // NOTE - SHOULD BE USING CONSTANTS
        
        SetValue("TurnSpeed", TurnSpeed);
        SetValue("SpinSpeed", SpinSpeed);
        SetValue("CurrentSpinAngle", Turret.transform.rotation.eulerAngles.y);
        SetValue("TimeToPause", 0.5f);
        // set node parameters - connect them to the blackboard
        Turn.SpinSpeedKey = "SpinSpeed";
        //ShotDelay.TimeToWaitKey = "TimeToPause";
        // connect nodes
        //Firing.children.Add(Shot);
        //Firing.children.Add(ShotDelay);
        Turn.children.Add(Shot);
        TurretAI.children.Add(Turn);
        //RotateShoot.children.Add(Shot);
        //TurretAI.children.Add(RotateShoot);

        //TurretAI.children.Add(Turn);
        //TurretAI.children.Add(Shot);
        TreeRoot.children.Add(TurretAI);
        TreeRoot.tree = this;
        Turn.tree = this;
        Shot.tree = this;
        //ShotDelay.tree = this;
        TurretAI.tree = this;
        root = TreeRoot;

    }

    // we don't need an update - the base class will deal with that.
    // but, since we have one, we can use it to set some of the moveto parameters on the fly
    // which lets us tweak them in the inspector
    public override void Update()
    {
        SetValue("TurnSpeed", TurnSpeed);
        SetValue("SpinSpeed", SpinSpeed);
        SetValue("CurrentSpinAngle", Turret.transform.rotation.eulerAngles.y);
        base.Update();
        
    }
}
