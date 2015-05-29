#include <glib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

#include <stabber.h>
#include <expect.h>

#include "proftest.h"

void
presence_online(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/online");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to online (priority 0)"));
}

void
presence_online_with_message(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/online \"Hi there\"");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<status>Hi there</status>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to online (priority 0), \"Hi there\"."));
}

void
presence_away(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/away");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>away</show>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to away (priority 0)"));
}

void
presence_away_with_message(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/away \"I'm not here for a bit\"");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>away</show>"
        "<status>I'm not here for a bit</status>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to away (priority 0), \"I'm not here for a bit\"."));
}

void
presence_xa(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/xa");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>xa</show>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to xa (priority 0)"));
}

void
presence_xa_with_message(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/xa \"Gone to the shops\"");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>xa</show>"
        "<status>Gone to the shops</status>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to xa (priority 0), \"Gone to the shops\"."));
}

void
presence_dnd(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/dnd");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>dnd</show>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to dnd (priority 0)"));
}

void
presence_dnd_with_message(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/dnd \"Working\"");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>dnd</show>"
        "<status>Working</status>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to dnd (priority 0), \"Working\"."));
}

void
presence_chat(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/chat");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>chat</show>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to chat (priority 0)"));
}

void
presence_chat_with_message(void **state)
{
    prof_connect("stabber@localhost", "password");

    prof_input("/chat \"Free to talk\"");

    assert_true(stbbr_received(
    "<presence id=\"*\">"
        "<show>chat</show>"
        "<status>Free to talk</status>"
        "<c hash=\"sha-1\" xmlns=\"http://jabber.org/protocol/caps\" ver=\"*\" node=\"http://www.profanity.im\"/>"
    "</presence>"
    ));

    assert_true(prof_output_exact("Status set to chat (priority 0), \"Free to talk\"."));
}
