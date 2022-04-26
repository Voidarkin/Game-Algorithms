using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spin : Task
{
    public string SpinSpeedKey;
    public float SpinSpeed;
    public float initialY;
    public float RotationAmount = 0.0f;
    public override NodeResult Execute()
    {
        RotationAmount += SpinSpeed * Time.deltaTime;
        if (RotationAmount >= 180.0)
        {
            RotationAmount = 180.0f;    
        }
        GameObject go = tree.gameObject;
        go.transform.rotation = Quaternion.Euler(0, initialY + RotationAmount, 0);
        if (RotationAmount == 180.0)
            {
                Reset();
                return NodeResult.SUCCESS;
            }
        else
        {
            return NodeResult.RUNNING;
        }
    }

    public override void Reset()
    {
        SpinSpeed = (float)(tree.GetValue(SpinSpeedKey));
        GameObject go = tree.gameObject;
        initialY = go.transform.rotation.eulerAngles.y;
        RotationAmount = 0.0f;
        base.Reset();
    }

}
