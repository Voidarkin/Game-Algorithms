using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spin : Task {
    public string SpinSpeedKey;
    public float SpinSpeed;
    public float initialY;
    public float RotationAmount = 0.0f;
    public GameObject go;
    
	// Use this for initialization
    public override void Reset () {
        SpinSpeed = (float)(tree.GetValue(SpinSpeedKey));
        go = tree.gameObject;
        RotationAmount = 0.0f;
        foreach (Node child in children)
        {
            child.Reset();
        }
        base.Reset();
    }
	
	// Update is called once per frame
	public override NodeResult Execute () {
        RotationAmount += SpinSpeed * Time.deltaTime;
        tree.SetValue("CurrentSpinAngle", RotationAmount);
        
        if (RotationAmount > 360)
        {
            tree.SetValue("CurrentSpinAngle", 0);
            go.transform.Rotate(Vector3.up, 0, Space.Self);
            return NodeResult.SUCCESS;
        }
        else
        {
            go.transform.Rotate(Vector3.up, SpinSpeed * Time.deltaTime, Space.Self);
            foreach(Node child in children)
            {
                child.Execute();
            }
        }
        return NodeResult.RUNNING;
	}
    
}
