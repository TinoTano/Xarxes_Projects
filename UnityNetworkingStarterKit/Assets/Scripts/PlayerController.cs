﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayerController : NetworkBehaviour
{
    private Animator animator;

    const float RUNNING_SPEED = 10.0f;
    const float ROTATION_SPEED = 180.0f;

    // Name label ////////////////////
    public Transform nameLabelPosition;
    public Transform nameLabelPrefab;
    private TextMesh nameLabel;

    // Name syncing //////////////////////////////////
    [SyncVar(hook = "SyncNameChanged")]
    public string playerName = "Player";

    [Command]
    void CmdChangeName(string name) { playerName = name; }

    void SyncNameChanged(string name) { nameLabel.text = name; }

    private void OnGUI()
    {
        if (isLocalPlayer)
        {
            GUILayout.BeginArea(new Rect(Screen.width - 260, 10, 250, Screen.height - 20));
            playerName = GUILayout.TextField(playerName);
            if (GUILayout.Button("Change name"))
            {
                CmdChangeName(playerName);
            }
            GUILayout.EndArea();
        }
    }


    [SyncVar(hook = "OnSetAnimation")]
    string animationName;

    void setAnimation(string animName)
    {
        OnSetAnimation(animName);
        CmdSetAnimation(animName);
    }

    [Command]
    void CmdSetAnimation(string animName)
    {
        animationName = animName;
    }

    void OnSetAnimation(string animName)
    {
        if (animationName == animName) return;
        animationName = animName;
        animator.SetBool("Idling", false);
        animator.SetBool("Running", false);
        animator.SetBool("Running backwards", false);
        animator.ResetTrigger("Jumping");
        animator.ResetTrigger("Kicking");
        if (animationName == "Idling") animator.SetBool("Idling", true);
        else if (animationName == "Running") animator.SetBool("Running", true);
        else if (animationName == "Running backwards") animator.SetBool("Running backwards", true);
        else if (animationName == "Jumping") animator.SetTrigger("Jumping");
        else if (animationName == "Kicking") animator.SetTrigger("Kicking");
    }

    // Virtual methods ///////////////////////////////

    // Use this for initialization
    void Start ()
    {
        animator = GetComponent<Animator>();

        nameLabel = Instantiate(nameLabelPrefab).GetComponent<TextMesh>();
        nameLabel.text = playerName;

        if (isLocalPlayer)
        {
            CameraController.player = transform;
        }
	}
	
	// Update is called once per frame
	void Update ()
    {
        nameLabel.transform.position = nameLabelPosition.position;
        nameLabel.transform.rotation = Quaternion.identity;

        if (!isLocalPlayer) return;

        Vector3 translation = new Vector3();
        float angle = 0.0f;

        float horizontalAxis = Input.GetAxis("Horizontal");
        float verticalAxis = Input.GetAxis("Vertical");

        if (verticalAxis  > 0.0)
        {
            setAnimation("Running");
            translation += new Vector3(0.0f, 0.0f, verticalAxis * RUNNING_SPEED * Time.deltaTime);
            transform.Translate(translation);
        }
        else if (verticalAxis < 0.0)
        {
            setAnimation("Running backwards");
            translation += new Vector3(0.0f, 0.0f, verticalAxis * RUNNING_SPEED * Time.deltaTime * 0.5f);
            transform.Translate(translation);
        }
        else
        {
            setAnimation("Idling");
        }

        if (horizontalAxis > 0.0f)
        {
            angle = horizontalAxis * Time.deltaTime * ROTATION_SPEED;
            transform.Rotate(new Vector3(0.0f, 1.0f, 0.0f), angle);
        }
        else if (horizontalAxis < 0.0f)
        {
            angle = horizontalAxis * Time.deltaTime * ROTATION_SPEED;
            transform.Rotate(new Vector3(0.0f, 1.0f, 0.0f), angle);
        }

        if (Input.GetButton("Jump"))
        {
            setAnimation("Jumping");
        }

        if (Input.GetButton("Fire1"))
        {
            setAnimation("Kicking");
        }
	}

    private void OnDestroy()
    {
        if (nameLabel != null)
        {
            Destroy(nameLabel.gameObject);
        }
    }
}
