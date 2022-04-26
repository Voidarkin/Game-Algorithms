using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{

    public float health = 15.0f;
    public float maxHealth = 20.0f;
    public float healthLength = 1.0f;

    float leftside;
    float rightside;

    public LineRenderer green;
    public LineRenderer red;

    public GameObject offset;

    Camera cam;

    private void Awake()
    {
        cam = Camera.main;
    }

    // Start is called before the first frame update
    void Start()
    {
        //healthLength /= 2.0f;
    }

    // Update is called once per frame
    void Update()
    {
        leftside = healthLength / 2;
        rightside = healthLength / 2;
        
        
        offset.transform.LookAt(cam.transform);

        Vector3 pos = offset.transform.position;
        
        Vector3 left = offset.transform.right;

        if (health <= 0.0f)
        {
            green.positionCount = 0;
            red.positionCount = 2;
            red.SetPosition(0, pos - left * leftside);
            red.SetPosition(1, pos + left * rightside);

            Destroy(this.transform.parent.gameObject);
        }
        else if(health >= maxHealth)
        {
            green.positionCount = 2;
            red.positionCount = 0;
            green.SetPosition(0, pos - left * leftside);
            green.SetPosition(1, pos + left * rightside);
        }
        else
        {
            green.positionCount = 2;
            red.positionCount = 2;
            float scale = (health / maxHealth) - 0.5f;
 
            green.SetPosition(0, pos + left * leftside);
            green.SetPosition(1, pos - left * scale * healthLength);
            red.SetPosition(0, pos - left * scale * healthLength);
            red.SetPosition(1, pos - left * rightside);

        }
    }
}
