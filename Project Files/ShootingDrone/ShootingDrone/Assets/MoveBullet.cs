using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveBullet : MonoBehaviour
{
    public float Speed = 100.0f;
    public float elapsedTime;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(transform.forward * Speed * Time.deltaTime, Space.World);
        elapsedTime += Time.deltaTime;
        if (elapsedTime > 3.0f)
        {
            Destroy(gameObject);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        Health h = other.transform.gameObject.GetComponent<Health>();
        if (h != null)
        {
            h.TakeDamage();
        }
        else
        {
            Destroy(other.transform.gameObject);

        }
        Destroy(gameObject);
    }
}
