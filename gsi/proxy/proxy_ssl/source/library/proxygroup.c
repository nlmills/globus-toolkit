
#include <stdio.h>
#include <openssl/err.h>
#include <openssl/asn1_mac.h>


#include "proxy_ssl_internal.h"
#include "proxygroup.h"

/**
 * @ingroup proxygroup
 *
 * Creates an ASN1_METHOD structure, which contains
 * pointers to routines that convert any PROXYGROUP
 * structure to its associated ASN.1 DER encoded form
 * and vice-versa.
 *
 * @return the ASN1_METHOD object
 */
ASN1_METHOD * PROXYGROUP_asn1_meth()
{
    static ASN1_METHOD proxygroup_asn1_meth =
    {
        (int (*)())   i2d_PROXYGROUP,
        (char *(*)()) d2i_PROXYGROUP,
        (char *(*)()) PROXYGROUP_new,
        (void (*)()) PROXYGROUP_free
    };
    return (&proxygroup_asn1_meth);
}

/**
 * @ingroup proxygroup
 *
 * Allocates and initializes a new PROXYGROUP structure.
 *
 * @return pointer to the new PROXYGROUP
 */
PROXYGROUP * PROXYGROUP_new()
{
    ASN1_CTX                            c;
    PROXYGROUP *                        ret;

    ret = NULL;

    M_ASN1_New_Malloc(ret, PROXYGROUP);
    M_ASN1_New(ret->group_name, M_ASN1_OCTET_STRING_new);
    ret->attached_group = (ASN1_BOOLEAN *)OPENSSL_malloc(sizeof(ASN1_BOOLEAN));
    *(ret->attached_group) = 1;
    return (ret);
    M_ASN1_New_Error(ASN1_F_PROXYGROUP_NEW);
}

/**
 * @ingroup proxygroup
 *
 * Frees the PROXYGROUP structure
 * 
 * @param group pointer ot the PROXYGROUP structure
 * to be freed
 */
void PROXYGROUP_free(
    PROXYGROUP *                        group)
{
    if(group == NULL) return;
    M_ASN1_OCTET_STRING_free(group->group_name);
    OPENSSL_free(group->attached_group);
    group->attached_group = NULL;
    OPENSSL_free(group);
}

/**
 * @ingroup proxygroup
 *
 * Makes a copy of the PROXYGROUP
 *
 * @param group the PROXYGROUP to be copied
 *
 * @return the new copied PROXYGROUP
 */
PROXYGROUP * PROXYGROUP_dup(
    PROXYGROUP *                        group)
{
    return ((PROXYGROUP *) ASN1_dup((int (*)())i2d_PROXYGROUP,
                                    (char *(*)())d2i_PROXYGROUP,
                                    (char *)group));
}

/**
 * @ingroup proxygroup
 *
 * Compares the two PROXYGROUP structures by
 * comparing each field in the two structures.
 * 
 * @param a the first PROXYGROUP
 * @param b the second PROXYGROUP
 *
 * @return an integer - the result of the comparison.
 * The comparison compares each of the fields, so if any
 * of those fields are equal, 0 is returned.  A nonzero value is
 * returned otherwise.
 */
int PROXYGROUP_cmp(
    const PROXYGROUP *                  a,
    const PROXYGROUP *                  b)
{
    if(ASN1_OCTET_STRING_cmp(a->group_name, b->group_name) &&
       (a->attached_group == b->attached_group))
    {
        return 1;
    }
    return 0;
}

/**
 * prints the PROXYGROUP struct in a readable format
 * using a BIO stream
 *
 * @param bp the BIO * field to print to - see openssl docs for more info
 * @param group the PROXYGROUP to print
 *
 * @return the length of bytes printed, -1 or -2 if an error
 */
int PROXYGROUP_print(
    BIO *                               bp,
    PROXYGROUP *                        group)
{
    int                                 ret,
                                        tmpret;

    ret = BIO_printf(bp, "PROXYGROUP::GroupName: ");
    if(ret < 0) { return ret; }

    tmpret = ASN1_STRING_print(bp, group->group_name);
    if(tmpret < 0) { return tmpret; }
    ret += tmpret;

    tmpret = BIO_printf(bp, "\nPROXYGROUP::AttachedGroup: %s\n", 
                        group->attached_group ? "TRUE" : "FALSE");
    if(tmpret < 0) { return tmpret; }

    return (ret + tmpret);
}

/**
 * prints the PROXYGROUP struct in a readable format
 * using a FILE * stream
 *
 * @param fp the file stream to print to
 * @param group the PROXYGROUP structure to print
 *
 * @return the number of bytes printed, -1 or -2 if an error
 */ 
int PROXYGROUP_print_fp(
    FILE *                              fp,
    PROXYGROUP *                        group)
{
    int                                 ret;

    BIO * bp = BIO_new(BIO_s_file());
    BIO_set_fp(bp, fp, BIO_NOCLOSE);
    ret = PROXYGROUP_print(bp, group);
    BIO_free(bp);

    return (ret);
}

/**
 * Sets the name of the group a proxy cert is in
 *
 * @param group the PROXYGROUP to set the name of
 * @param group_name the name to set it to
 * @param length the length of the name (in bytes)
 *
 * @return 1 on success, 0 on error
 */
int PROXYGROUP_set_name(
    PROXYGROUP *                        group,
    char *                              group_name,
    long                                length)
{
    if(group_name != NULL)
    {
        return ASN1_OCTET_STRING_set(group->group_name, group_name, length);
    }
    return 0;
}

/**
 * Gets the name of the PROXYGROUP
 *
 * @param group the PROXYGROUP to get the name of
 * @param length the length of the name (will be set)
 * 
 * @return the name
 */
char * PROXYGROUP_get_name(
    PROXYGROUP *                        group,
    long *                              length)
{
    *length = group->group_name->length;
    return group->group_name->data;
}

/**
 * Sets the value of the PROXYGROUP's attached field to 
 * true or false.  
 *
 * @param group the PROXYGROUP to set the attached_group field of
 * @param attached the value to set it to
 *
 * @return 1 on success, 0 on error
 */ 
int PROXYGROUP_set_attached(
    PROXYGROUP *                        group,
    ASN1_BOOLEAN                        attached)
{
    *(group->attached_group) = attached;
    return 1;
}

/**
 * Gets the attached setting of a PROXYGROUP
 *
 * @param group the PROXYGROUP to get the attached field of
 *
 * @return the attached value
 */
ASN1_BOOLEAN * PROXYGROUP_get_attached(
    PROXYGROUP *                        group)
{
    return group->attached_group;
}

/**
 * Converts the PROXYGROUP struct from internal
 * form to its DER encoded form
 *
 * @param a the PROXYGROUP to convert
 * @param pp the resulting byte array of DER encoding
 *
 * @return the number of bytes of the DER encoded string
 */
int i2d_PROXYGROUP(
    PROXYGROUP *                        a,
    unsigned char **                    pp)
{
    M_ASN1_I2D_vars(a);

    M_ASN1_I2D_len(a->group_name,
                   i2d_ASN1_OCTET_STRING);
    M_ASN1_I2D_len(*(a->attached_group),
                   i2d_ASN1_BOOLEAN);
    M_ASN1_I2D_seq_total();
    M_ASN1_I2D_put(a->group_name, i2d_ASN1_OCTET_STRING);
    M_ASN1_I2D_put(*(a->attached_group), i2d_ASN1_BOOLEAN);

    M_ASN1_I2D_finish();
}

/**
 * Converts a PROXYGROUP struct from its DER encoded
 * form to its internal (data structure) form
 *
 * @param a the resulting PROXYGROUP struct in internal form
 * @param pp the DER encoded string of a PROXYGROUP (hopefully)
 * @param length the length of pp
 *
 * @return the resulting PROXYGROUP struct
 */ 
PROXYGROUP * d2i_PROXYGROUP(
    PROXYGROUP **                       a,
    unsigned char **                    pp,
    long                                length)
{
    M_ASN1_D2I_vars(a, PROXYGROUP *, PROXYGROUP_new);
    
    M_ASN1_D2I_Init();
    M_ASN1_D2I_start_sequence();
    M_ASN1_D2I_get(ret->group_name, d2i_ASN1_OCTET_STRING);
    
    if((c.slen != 0) && (M_ASN1_next == (V_ASN1_UNIVERSAL|V_ASN1_BOOLEAN)))
    {
        c.q = c.p;
        if(d2i_ASN1_BOOLEAN(ret->attached_group, &c.p, c.slen) < 0) goto err;
        c.slen -= (c.p - c.q);
    }

    M_ASN1_D2I_Finish(a, PROXYGROUP_free, ASN1_F_D2I_PROXYGROUP);
}
